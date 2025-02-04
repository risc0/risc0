package circom

import (
	"bytes"
	"encoding/binary"
	"errors"
	"fmt"
	"github.com/consensys/gnark-crypto/ecc/bn254"
	bn254fp "github.com/consensys/gnark-crypto/ecc/bn254/fp"
	bn254fr "github.com/consensys/gnark-crypto/ecc/bn254/fr"
	bn254fft "github.com/consensys/gnark-crypto/ecc/bn254/fr/fft"
	"github.com/consensys/gnark/backend/groth16"
	bn254groth16 "github.com/consensys/gnark/backend/groth16/bn254"
	"github.com/consensys/gnark/constraint"
	bn254r1cs "github.com/consensys/gnark/constraint/bn254"
	"github.com/consensys/gnark/logger"
	"golang.org/x/sync/errgroup"
	"io"
	"math/big"
)

type ZKey struct {
	zkeyHeader

	coefficients []coefficient

	VK bn254groth16.VerifyingKey
	PK bn254groth16.ProvingKey
}

type zkeyHeader struct {
	q *big.Int
	r *big.Int

	nVars      uint32
	nPublic    uint32
	domainSize uint32
}

type coefficient struct {
	matrix     uint32
	constraint uint32
	signal     uint32
	value      bn254fp.Element
}

// readFieldMont reads a little Endian field element already in Montgomery form.
func readFieldMont(r io.Reader, z *bn254fp.Element) error {
	var buf [32]byte
	if _, err := io.ReadFull(r, buf[:]); err != nil {
		return err
	}

	z[0] = binary.LittleEndian.Uint64(buf[:8])
	z[1] = binary.LittleEndian.Uint64(buf[8:16])
	z[2] = binary.LittleEndian.Uint64(buf[16:24])
	z[3] = binary.LittleEndian.Uint64(buf[24:32])

	return nil
}

func readG1Affine(r io.Reader, p *bn254.G1Affine) error {
	if err := readFieldMont(r, &p.X); err != nil {
		return err
	}
	if err := readFieldMont(r, &p.Y); err != nil {
		return err
	}

	return nil
}

func readG2Affine(r io.Reader, p *bn254.G2Affine) error {
	if err := readFieldMont(r, &p.X.A0); err != nil {
		return err
	}
	if err := readFieldMont(r, &p.X.A1); err != nil {
		return err
	}
	if err := readFieldMont(r, &p.Y.A0); err != nil {
		return err
	}
	if err := readFieldMont(r, &p.Y.A1); err != nil {
		return err
	}

	return nil
}

func readZKey(binFile *BinFile) (*ZKey, error) {
	zkey := &ZKey{}
	header := &zkey.zkeyHeader

	// 0x01 Header section
	r := bytes.NewReader(binFile.GetHeader())

	protocolID, err := ReadUint32(r)
	if err != nil {
		return nil, err
	}
	if protocolID != 1 {
		return nil, fmt.Errorf("invalid protocol")
	}
	if r.Len() != 0 {
		return nil, ErrInvalidSize
	}

	r = bytes.NewReader(binFile.Sections[0x02])

	n8q, err := ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.q, err = ReadBigInt(r, n8q)
	if err != nil {
		return nil, err
	}

	n8r, err := ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.r, err = ReadBigInt(r, n8r)
	if err != nil {
		return nil, err
	}

	header.nVars, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.nPublic, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.domainSize, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}

	vk := &zkey.VK
	if err := readG1Affine(r, &vk.G1.Alpha); err != nil {
		return nil, err
	}
	if err := readG1Affine(r, &vk.G1.Beta); err != nil {
		return nil, err
	}
	if err := readG2Affine(r, &vk.G2.Beta); err != nil {
		return nil, err
	}
	if err := readG2Affine(r, &vk.G2.Gamma); err != nil {
		return nil, err
	}
	if err := readG1Affine(r, &vk.G1.Delta); err != nil {
		return nil, err
	}
	if err := readG2Affine(r, &vk.G2.Delta); err != nil {
		return nil, err
	}

	if r.Len() != 0 {
		return nil, ErrInvalidSize
	}

	// fill the proving key from the verification key
	pk := &zkey.PK
	pk.G1.Alpha = vk.G1.Alpha
	pk.G1.Beta = vk.G1.Beta
	pk.G1.Delta = vk.G1.Delta
	pk.G2.Beta = vk.G2.Beta
	pk.G2.Delta = vk.G2.Delta

	return zkey, nil
}

func readCoefSection(section []byte) ([]coefficient, error) {
	r := bytes.NewReader(section)

	nbCoefs, err := ReadUint32(r)
	if err != nil {
		return nil, err
	}
	coefs := make([]coefficient, nbCoefs)
	for i := range coefs {
		c := &coefs[i]
		c.matrix, err = ReadUint32(r)
		c.constraint, err = ReadUint32(r)
		c.signal, err = ReadUint32(r)
		if err := readFieldMont(r, &c.value); err != nil {
			return nil, err
		}
	}
	if r.Len() != 0 {
		return nil, ErrInvalidSize
	}

	return coefs, nil
}

func readG1Section(section []byte, nbPoints uint32, res *[]bn254.G1Affine) error {
	*res = make([]bn254.G1Affine, nbPoints)

	r := bytes.NewReader(section)
	points := *res
	for i := range points {
		if err := readG1Affine(r, &points[i]); err != nil {
			return fmt.Errorf("invalid G1 point: %w", err)
		}
	}
	if r.Len() != 0 {
		return ErrInvalidSize
	}

	return nil
}

func readG2Section(section []byte, nbPoints uint32, res *[]bn254.G2Affine) error {
	*res = make([]bn254.G2Affine, nbPoints)

	r := bytes.NewReader(section)
	points := *res
	for i := range points {
		if err := readG2Affine(r, &points[i]); err != nil {
			return fmt.Errorf("invalid G2 point: %w", err)
		}
	}
	if r.Len() != 0 {
		return ErrInvalidSize
	}

	return nil
}

// ReadZKey reads a circom ZKey binary file and returns the proving and verifying key.
//
// See: https://github.com/iden3/snarkjs/blob/master/src/zkey_utils.js
func ReadZKey(r io.Reader, cs constraint.ConstraintSystem) (groth16.ProvingKey, groth16.VerifyingKey, error) {
	r1cs := cs.(*bn254r1cs.R1CS)
	log := logger.Logger()

	if len(r1cs.CommitmentInfo.(constraint.Groth16Commitments)) != 0 {
		log.Panic().Msg("Constraint system must not contain commitments")
	}

	// get R1CS nb constraints, wires and public/private inputs
	nbWires := r1cs.NbInternalVariables + r1cs.GetNbPublicVariables() + r1cs.GetNbSecretVariables()
	nbPublicWires := r1cs.GetNbPublicVariables()
	nbPrivateWires := r1cs.GetNbSecretVariables() + r1cs.NbInternalVariables

	// Setting group for fft
	domain := bn254fft.NewDomain(uint64(r1cs.GetNbConstraints() + r1cs.GetNbPublicVariables()))

	binFile, err := ReadBinFile(r, "zkey", 1)
	if err != nil {
		return nil, nil, fmt.Errorf("failed to parse file: %w", err)
	}

	// 0x01 Header section
	zKey, err := readZKey(binFile)
	if err != nil {
		return nil, nil, fmt.Errorf("invalid header section: %w", err)
	}

	log.Debug().Uint32("nVars", zKey.nVars).Uint32("nPublic", zKey.nPublic).
		Uint32("domainSize", zKey.domainSize).Msg("ZKEY header")

	// validate the header
	if zKey.r.Cmp(bn254fr.Modulus()) != 0 || zKey.q.Cmp(bn254fp.Modulus()) != 0 {
		return nil, nil, ErrInvalidField
	}
	if zKey.nVars != uint32(nbWires) ||
		zKey.nPublic+1 != uint32(nbPublicWires) || zKey.nVars-(zKey.nPublic+1) != uint32(nbPrivateWires) {
		return nil, nil, fmt.Errorf("invalid CS")
	}
	if zKey.domainSize != uint32(domain.Cardinality) {
		return nil, nil, errors.New("invalid domain size")
	}

	g := new(errgroup.Group)
	vk, pk := &zKey.VK, &zKey.PK

	// 0x03 IC section
	g.Go(func() error {
		if err := readG1Section(binFile.Sections[0x03], zKey.nPublic+1, &vk.G1.K); err != nil {
			return fmt.Errorf("invalid IC section: %w", err)
		}
		return nil
	})

	// 0x04 Coef section
	// ignore

	// 0x05 A section
	g.Go(func() error {
		if err := readG1Section(binFile.Sections[0x05], zKey.nVars, &pk.G1.A); err != nil {
			return fmt.Errorf("invalid A section: %w", err)
		}
		return nil
	})

	// 0x06 B1 section
	g.Go(func() error {
		if err := readG1Section(binFile.Sections[0x06], zKey.nVars, &pk.G1.B); err != nil {
			return fmt.Errorf("invalid B1 section: %w", err)
		}
		return nil
	})

	// 0x07 B2 section
	g.Go(func() error {
		if err := readG2Section(binFile.Sections[0x07], zKey.nVars, &pk.G2.B); err != nil {
			return fmt.Errorf("invalid B2 section: %w", err)
		}
		return nil
	})

	// 0x08 C section
	g.Go(func() error {
		if err := readG1Section(binFile.Sections[0x08], zKey.nVars-(zKey.nPublic+1), &pk.G1.K); err != nil {
			return fmt.Errorf("invalid C section: %w", err)
		}
		return nil
	})

	// 0x09 H section
	g.Go(func() error {
		if err := readG1Section(binFile.Sections[0x09], zKey.domainSize, &pk.G1.Z); err != nil {
			return fmt.Errorf("invalid H section: %w", err)
		}
		return nil
	})

	// 0x0A contribution section
	// ignore

	// wait until all sections have been read
	if err := g.Wait(); err != nil {
		return nil, nil, err
	}

	// precompute the necessary values (p, gammaNeg, deltaNeg)
	if err := zKey.VK.Precompute(); err != nil {
		return nil, nil, fmt.Errorf("failed to precompute verification key: %w", err)
	}

	pk.Domain = *domain

	// precompute the necessary values (InfinityA, InfinityB)
	if err := precomputeProvingKey(pk); err != nil {
		return nil, nil, fmt.Errorf("failed to precompute proving key: %w", err)
	}

	return pk, vk, nil
}

func precomputeProvingKey(pk *bn254groth16.ProvingKey) error {
	nbWires := len(pk.G1.A)

	// mark points in A that are at infinity and filter them
	pk.InfinityA = make([]bool, len(pk.G1.A))

	n := 0
	for i := range pk.G1.A {
		a := &pk.G1.A[i]
		if a.IsInfinity() {
			pk.InfinityA[i] = true
			continue
		}
		pk.G1.A[n] = *a
		n++
	}
	pk.G1.A = pk.G1.A[:n]
	pk.NbInfinityA = uint64(nbWires - n)

	// mark points in B that are at infinity and filter them
	pk.InfinityB = make([]bool, len(pk.G1.B))

	// hint for the compiler
	if len(pk.G1.B) != len(pk.G2.B) {
		panic("invalid pk")
	}

	n = 0
	for i := range pk.G1.B {
		b1, b2 := &pk.G1.B[i], &pk.G2.B[i]
		infinity := b1.IsInfinity()
		if infinity != b2.IsInfinity() {
			return errors.New("inconsistent B points")
		}
		if infinity {
			pk.InfinityB[i] = true
			continue
		}
		pk.G1.B[n] = *b1
		pk.G2.B[n] = *b2
		n++
	}
	pk.G1.B = pk.G1.B[:n]
	pk.G2.B = pk.G2.B[:n]
	pk.NbInfinityB = uint64(nbWires - n)

	return nil
}
