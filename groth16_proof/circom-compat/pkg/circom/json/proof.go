package json

import (
	"errors"
	"github.com/consensys/gnark-crypto/ecc/bn254"
	bn254fp "github.com/consensys/gnark-crypto/ecc/bn254/fp"
	"github.com/consensys/gnark/backend/groth16"
	bn254groth16 "github.com/consensys/gnark/backend/groth16/bn254"
	"math/big"
)

const (
	ProofProtocol string = "groth16"
	ProofCurve    string = "bn254"
)

type FPElement bn254fp.Element

type G1 [3]*FPElement
type G2 [3][2]*FPElement

// Proof represents a Groth16 proof in its JSON form.
type Proof struct {
	A        G1     `json:"pi_a"`
	B        G2     `json:"pi_b"`
	C        G1     `json:"pi_c"`
	Protocol string `json:"protocol"`
	Curve    string `json:"curve"`
}

func (e *FPElement) MarshalText() ([]byte, error) {
	var v big.Int
	(*bn254fp.Element)(e).BigInt(&v)
	return v.MarshalText()
}

func (e *FPElement) UnmarshalText(text []byte) error {
	var v big.Int
	if err := v.UnmarshalText(text); err != nil {
		return err
	}
	(*bn254fp.Element)(e).SetBigInt(&v)
	return nil
}

func NewProof(proof groth16.Proof) *Proof {
	bn254Proof := proof.(*bn254groth16.Proof)

	jp := &Proof{}
	jp.A.FromG1Affine(&bn254Proof.Ar)
	jp.B.FromG2Affine(&bn254Proof.Bs)
	jp.C.FromG1Affine(&bn254Proof.Krs)
	jp.Protocol = ProofProtocol
	jp.Curve = ProofCurve

	return jp
}

func (jp *Proof) ToGroth16Proof() (groth16.Proof, error) {
	if jp.Protocol != ProofProtocol || jp.Curve != ProofCurve {
		return nil, errors.New("invalid proof type")
	}

	p := &bn254groth16.Proof{}
	p.Ar = jp.A.G1Affine()
	p.Bs = jp.B.G2Affine()
	p.Krs = jp.C.G1Affine()

	return p, nil
}

func (g *G1) FromG1Affine(p *bn254.G1Affine) {
	var pj bn254.G1Jac
	pj.FromAffine(p)
	*g = [3]*FPElement{(*FPElement)(&pj.X), (*FPElement)(&pj.Y), (*FPElement)(&pj.Z)}
}

func (g *G1) G1Affine() bn254.G1Affine {
	var p bn254.G1Affine
	p.FromJacobian(&bn254.G1Jac{
		X: bn254fp.Element(*g[0]),
		Y: bn254fp.Element(*g[1]),
		Z: bn254fp.Element(*g[2]),
	})
	return p
}

func (g *G2) FromG2Affine(p *bn254.G2Affine) {
	var pj bn254.G2Jac
	pj.FromAffine(p)
	*g = [3][2]*FPElement{
		{(*FPElement)(&pj.X.A0), (*FPElement)(&pj.X.A1)},
		{(*FPElement)(&pj.Y.A0), (*FPElement)(&pj.Y.A1)},
		{(*FPElement)(&pj.Z.A0), (*FPElement)(&pj.Z.A1)},
	}
}

func (g *G2) G2Affine() (p bn254.G2Affine) {
	var pj bn254.G2Jac
	pj.X.A0, pj.X.A1 = bn254fp.Element(*g[0][0]), bn254fp.Element(*g[0][1])
	pj.Y.A0, pj.Y.A1 = bn254fp.Element(*g[1][0]), bn254fp.Element(*g[1][1])
	pj.Z.A0, pj.Z.A1 = bn254fp.Element(*g[2][0]), bn254fp.Element(*g[2][1])
	p.FromJacobian(&pj)

	return p
}
