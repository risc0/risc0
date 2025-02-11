package circom

import (
	"bytes"
	"errors"
	"fmt"
	bn254fr "github.com/consensys/gnark-crypto/ecc/bn254/fr"
	"github.com/consensys/gnark/constraint"
	bn254r1cs "github.com/consensys/gnark/constraint/bn254"
	"github.com/consensys/gnark/logger"
	"io"
	"math/big"
)

var (
	ErrInvalidSize         = errors.New("invalid section size")
	ErrInvalidField        = errors.New("invalid field")
	ErrInvalidNWires       = errors.New("invalid number of wires")
	ErrInvalidOneWireLabel = errors.New("ONE wire must always map to 0")
)

type R1CS struct {
	r1csHeader

	labels []uint64

	genericGate constraint.BlueprintID
	cs          *bn254r1cs.R1CS
}

type r1csHeader struct {
	fs           uint32   // Size in bytes of a field element
	r            *big.Int // Modulus of the field
	nWires       uint32   // Number of wires, including the ONE wire
	nPubOutputs  uint32   // Number of public outputs
	nPubInputs   uint32   // Number of public inputs
	nPrvInputs   uint32   // Number of private inputs
	nLabels      uint64   // Number of Labels
	nConstraints uint32   // Number of constraints
}

func (c *R1CS) readCoefficient(r io.Reader) (coeff constraint.Element, err error) {
	b, err := ReadBigInt256(r)
	if err != nil {
		return coeff, err
	}
	var e bn254fr.Element
	e.SetBigInt(b)
	copy(coeff[:], e[:])

	return coeff, err
}

func (c *R1CS) readLinearExpression(r io.Reader) (constraint.LinearExpression, error) {
	nTerms, err := ReadUint32(r)
	if err != nil {
		return nil, err
	}

	lc := make([]constraint.Term, nTerms)
	for i := range lc {
		variableID, err := ReadUint32(r)
		if err != nil {
			return nil, err
		}
		coeff, err := c.readCoefficient(r)
		if err != nil {
			return nil, err
		}

		lc[i] = c.cs.MakeTerm(coeff, int(variableID))
	}

	return lc, nil
}

func (c *R1CS) readR1C(r io.Reader) (r1c constraint.R1C, err error) {
	r1c.L, err = c.readLinearExpression(r)
	if err != nil {
		return r1c, err
	}
	r1c.R, err = c.readLinearExpression(r)
	if err != nil {
		return r1c, err
	}
	r1c.O, err = c.readLinearExpression(r)
	if err != nil {
		return r1c, err
	}

	return r1c, nil
}

func (c *R1CS) readConstraintsSection(section []byte) error {
	r := bytes.NewReader(section)

	for i := uint32(0); i < c.r1csHeader.nConstraints; i++ {
		r1c, err := c.readR1C(r)
		if err != nil {
			return err
		}
		c.cs.AddR1C(r1c, c.genericGate)
	}
	if r.Len() != 0 {
		return ErrInvalidSize
	}

	return nil
}

func (c *R1CS) readLabelsSection(section []byte) (err error) {
	r := bytes.NewReader(section)

	c.labels = make([]uint64, c.r1csHeader.nWires)
	for i := range c.labels {
		c.labels[i], err = ReadUint64(r)
		if err != nil {
			return err
		}
	}
	if r.Len() != 0 {
		return ErrInvalidSize
	}

	if c.labels[0] != 0 {
		return ErrInvalidOneWireLabel
	}

	return nil
}

func newR1CS(section []byte) (*R1CS, error) {
	var err error
	builder := &R1CS{}
	header := &builder.r1csHeader

	r := bytes.NewReader(section)

	header.fs, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.r, err = ReadBigInt(r, header.fs)
	if err != nil {
		return nil, err
	}
	header.nWires, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.nPubOutputs, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.nPubInputs, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.nPrvInputs, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	header.nLabels, err = ReadUint64(r)
	if err != nil {
		return nil, err
	}
	header.nConstraints, err = ReadUint32(r)
	if err != nil {
		return nil, err
	}
	if r.Len() != 0 {
		return nil, ErrInvalidSize
	}

	// validate the header
	if header.fs != 32 || header.r.Cmp(bn254fr.Modulus()) != 0 {
		return nil, ErrInvalidField
	}
	// the number of wires must be at least equal to the number of outputs and inputs plus the one wire
	if header.nWires < 1+header.nPubOutputs+header.nPubInputs+header.nPrvInputs {
		return nil, ErrInvalidNWires
	}

	r1cs := bn254r1cs.NewR1CS(int(header.nConstraints))
	builder.cs = r1cs
	builder.genericGate = r1cs.AddBlueprint(&constraint.BlueprintGenericR1C{})

	r1cs.AddPublicVariable("1") // the "ONE" wire
	for i := uint32(0); i < header.nPubOutputs; i++ {
		r1cs.AddPublicVariable(fmt.Sprintf("PubOut_%d", i))
	}
	for i := uint32(0); i < header.nPubInputs; i++ {
		r1cs.AddPublicVariable(fmt.Sprintf("PubIn_%d", i))
	}
	for i := uint32(0); i < header.nPrvInputs; i++ {
		r1cs.AddSecretVariable(fmt.Sprintf("PrvIn_%d", i))
	}
	for i := 1 + header.nPubOutputs + header.nPubInputs + header.nPrvInputs; i < header.nWires; i++ {
		r1cs.AddSecretVariable(fmt.Sprintf("v_%d", i))
	}

	return builder, nil
}

// ReadR1CS reads a circom R1CS binary file and returns a constraint.ConstraintSystem.
//
// The format is defined here: https://github.com/iden3/r1csfile/blob/master/doc/r1cs_bin_format.md.
func ReadR1CS(r io.Reader) (constraint.ConstraintSystem, error) {
	log := logger.Logger()

	file, err := ReadBinFile(r, "r1cs", 1)
	if err != nil {
		return nil, fmt.Errorf("failed to parse file: %w", err)
	}

	// 0x01 Header section
	r1cs, err := newR1CS(file.GetHeader())
	if err != nil {
		return nil, fmt.Errorf("invalid header section: %w", err)
	}

	log.Debug().Uint32("nWires", r1cs.nWires).Uint32("nPubOutputs", r1cs.nPubOutputs).
		Uint32("nPubInputs", r1cs.nPubInputs).Uint32("nPrvInputs", r1cs.nPrvInputs).
		Uint32("nConstraints", r1cs.nConstraints).Msg("R1CS header")

	// 0x02: Constraints section
	if err := r1cs.readConstraintsSection(file.Sections[0x02]); err != nil {
		return nil, fmt.Errorf("invalid constraints section: %w", err)
	}

	// 0x03 WireId2LabelId Map Section
	// ignore

	return r1cs.cs, err
}
