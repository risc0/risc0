package circom

import (
	"bytes"
	"encoding/binary"
	"errors"
	"fmt"
	bn254fr "github.com/consensys/gnark-crypto/ecc/bn254/fr"
	"github.com/consensys/gnark/backend/witness"
	"github.com/consensys/gnark/constraint"
	"github.com/consensys/gnark/logger"
	"io"
	"math/big"
)

var bigOne = big.NewInt(1)

type WTNS struct {
	wtnsHeader

	nbPublic uint32
	nbSecret uint32

	w witness.Witness
}

type wtnsHeader struct {
	fs         uint32   // Size in bytes of a field element
	q          *big.Int // Modulus of the field
	nWitnesses uint32   // Number of witnesses
}

func (wtns *WTNS) readWitnesses(src []byte) error {
	// check size first as we are potentially not reading the entire section
	if len(src) != int(wtns.nWitnesses)*int(wtns.fs) {
		return ErrInvalidSize
	}

	// unfortunately gnark does not offer an efficient way to initialize the witnesses
	// instead we convert the WTNS section to gnark binary data and then use UnmarshalBinary
	nInputs := wtns.nbPublic + wtns.nbSecret
	data := make([]byte, 12+32*(nInputs-1))
	dst := data

	// write the header
	binary.BigEndian.PutUint32(dst[0:4], wtns.nbPublic-1)
	binary.BigEndian.PutUint32(dst[4:8], wtns.nbSecret)
	binary.BigEndian.PutUint32(dst[8:12], nInputs-1)
	dst = dst[12:]

	// write all field elements in big endian
	for i := uint32(0); i < nInputs; i++ {
		if i == 0 {
			if value, err := ReadBigInt256(bytes.NewReader(src[:32])); err != nil {
				return err
			} else if value.Cmp(bigOne) != 0 {
				return errors.New("invalid ONE wire")
			}
			// advance the read buffer and continue reading field elements
			src = src[32:]
			continue
		}

		_ = dst[31] // early bounds check to guarantee safety of writes below

		// convert the 256-bit int from little endian to big endian
		binary.BigEndian.PutUint64(dst[0:8], binary.LittleEndian.Uint64(src[24:32]))
		binary.BigEndian.PutUint64(dst[8:16], binary.LittleEndian.Uint64(src[16:24]))
		binary.BigEndian.PutUint64(dst[16:24], binary.LittleEndian.Uint64(src[8:16]))
		binary.BigEndian.PutUint64(dst[24:32], binary.LittleEndian.Uint64(src[0:8]))

		// advance the buffers
		src, dst = src[32:], dst[32:]
	}

	if err := wtns.w.UnmarshalBinary(data); err != nil {
		return err
	}

	return nil
}

func readWTNS(section []byte) (*WTNS, error) {
	var err error
	wtns := &WTNS{}
	header := &wtns.wtnsHeader

	r := bytes.NewReader(section)

	header.fs, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.q, err = ReadBigInt(r, header.fs)
	if err != nil {
		return nil, err
	}
	header.nWitnesses, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	if r.Len() != 0 {
		return nil, ErrInvalidSize
	}

	return wtns, nil
}

// ReadWTNS reads a circom WTNS binary file and returns a witness.Witness.
//
// See: https://github.com/iden3/snarkjs/blob/master/src/wtns_utils.js
func ReadWTNS(r io.Reader, cs constraint.ConstraintSystem) (witness.Witness, error) {
	r1cs := cs.(constraint.R1CS)
	log := logger.Logger().With().Int("nInputs", r1cs.GetNbPublicVariables()+r1cs.GetNbSecretVariables()).Logger()

	binFile, err := ReadBinFile(r, "wtns", 2)
	if err != nil {
		return nil, fmt.Errorf("failed to parse file: %w", err)
	}

	// 0x01 Header section
	wtns, err := readWTNS(binFile.GetHeader())
	if err != nil {
		return nil, fmt.Errorf("invalid header section: %w", err)
	}

	log.Debug().Uint32("nWitnesses", wtns.nWitnesses).Msg("WTNS header")

	// validate the header
	if wtns.fs != 32 || wtns.q.Cmp(bn254fr.Modulus()) != 0 {
		return nil, ErrInvalidField
	}
	wtns.nbPublic = uint32(r1cs.GetNbPublicVariables())
	wtns.nbSecret = uint32(r1cs.GetNbSecretVariables())
	if wtns.nWitnesses < wtns.nbPublic+wtns.nbSecret {
		return nil, errors.New("invalid number of witnesses")
	}

	wtns.w, err = witness.New(r1cs.Field())
	if err != nil {
		return nil, fmt.Errorf("invalid constraint system: %w", err)
	}

	// 0x02 witness section
	if err := wtns.readWitnesses(binFile.Sections[0x02]); err != nil {
		return nil, fmt.Errorf("invalid witness section: %w", err)
	}

	return wtns.w, nil
}
