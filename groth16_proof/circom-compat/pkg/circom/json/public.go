package json

import (
	bn254fr "github.com/consensys/gnark-crypto/ecc/bn254/fr"
	"math/big"
)

type FRElement bn254fr.Element

type Public []FRElement

func (e *FRElement) MarshalText() ([]byte, error) {
	var v big.Int
	(*bn254fr.Element)(e).BigInt(&v)
	return v.MarshalText()
}

func (e *FRElement) UnmarshalText(text []byte) error {
	var v big.Int
	if err := v.UnmarshalText(text); err != nil {
		return err
	}
	(*bn254fr.Element)(e).SetBigInt(&v)
	return nil
}

func NewPublic(pubVariables []bn254fr.Element) Public {
	res := make(Public, 0, len(pubVariables))
	// the first wire is always one and must be ignored
	for i := range pubVariables[1:] {
		res = append(res, FRElement(pubVariables[i]))
	}
	return res
}
