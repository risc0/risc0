package circom

import (
	"encoding/binary"
	"fmt"
	"io"
	"math/big"
	"math/bits"
)

func ReadUint32(r io.Reader) (uint32, error) {
	var buf [4]byte
	if _, err := io.ReadFull(r, buf[:]); err != nil {
		return 0, err
	}
	return binary.LittleEndian.Uint32(buf[:]), nil
}

func ReadUint64(r io.Reader) (val uint64, err error) {
	var buf [8]byte
	if _, err := io.ReadFull(r, buf[:]); err != nil {
		return 0, err
	}
	return binary.LittleEndian.Uint64(buf[:]), nil
}

func ReadBigInt256(r io.Reader) (*big.Int, error) {
	// fast path for 64-bit architectures
	if bits.UintSize != 64 {
		return ReadBigInt(r, 32)
	}

	buf := make([]byte, 32)
	if _, err := io.ReadFull(r, buf); err != nil {
		return nil, err
	}

	var abs [4]big.Word
	abs[0] = big.Word(binary.LittleEndian.Uint64(buf[0:8]))
	abs[1] = big.Word(binary.LittleEndian.Uint64(buf[8:16]))
	abs[2] = big.Word(binary.LittleEndian.Uint64(buf[16:24]))
	abs[3] = big.Word(binary.LittleEndian.Uint64(buf[24:32]))

	return new(big.Int).SetBits(abs[:]), nil
}

func ReadBigInt(r io.Reader, size uint32) (*big.Int, error) {
	buf := make([]byte, size)
	if _, err := io.ReadFull(r, buf); err != nil {
		return nil, err
	}

	// reverse the byte order to convert from little-endian to big-endian
	for i, j := 0, len(buf)-1; i < j; i, j = i+1, j-1 {
		buf[i], buf[j] = buf[j], buf[i]
	}
	return new(big.Int).SetBytes(buf), nil
}

type BinFile struct {
	Version  uint32
	Sections map[uint32][]byte
}

func (f *BinFile) GetHeader() []byte {
	return f.Sections[0x01]
}

// ReadBinFile reads a circom binary file.
// See https://github.com/iden3/binfileutils
func ReadBinFile(r io.Reader, typeString string, maxVersion uint32) (*BinFile, error) {
	var magic [4]byte
	if _, err := io.ReadFull(r, magic[:]); err != nil {
		return nil, err
	}
	if string(magic[:]) != typeString {
		return nil, fmt.Errorf("invalid magic number")
	}
	version, err := ReadUint32(r)
	if err != nil {
		return nil, err
	}
	if version > maxVersion {
		return nil, fmt.Errorf("invalid version")
	}
	nSections, err := ReadUint32(r)
	if err != nil {
		return nil, err
	}
	sections := make(map[uint32][]byte, nSections)
	for i := uint32(0); i < nSections; i++ {
		id, err := ReadUint32(r)
		if err != nil {
			return nil, err
		}
		if _, contains := sections[id]; contains {
			return nil, fmt.Errorf("duplicate section: %x", id)
		}
		size, err := ReadUint64(r)
		if err != nil {
			return nil, err
		}
		section := make([]byte, size)
		if _, err := io.ReadFull(r, section); err != nil {
			return nil, err
		}

		sections[id] = section
	}

	return &BinFile{
		Version:  version,
		Sections: sections,
	}, nil
}
