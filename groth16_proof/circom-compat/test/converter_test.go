package test

import (
	"bytes"
	"github.com/consensys/gnark-crypto/ecc"
	"github.com/consensys/gnark/backend/groth16"
	"github.com/stretchr/testify/require"
	"testing"
)

func TestConvertCS(t *testing.T) {
	cs := loadConstraints(t, "multiplier2.r1cs")

	var buffer bytes.Buffer

	// Write the constraint system to the buffer
	_, err := cs.WriteTo(&buffer)
	require.NoError(t, err)

	// Read the constraint system from the buffer
	readCs := groth16.NewCS(ecc.BN254)
	_, err = readCs.ReadFrom(&buffer)
	require.NoError(t, err)

	require.Equal(t, cs.GetNbConstraints(), readCs.GetNbConstraints(), "Number of constraints mismatch")
	require.Equal(t, cs.GetNbPublicVariables(), readCs.GetNbPublicVariables(), "Number of public variables mismatch")
	require.Equal(t, cs.GetNbSecretVariables(), readCs.GetNbSecretVariables(), "Number of secret variables mismatch")
	require.Equal(t, cs.GetNbInternalVariables(), readCs.GetNbInternalVariables(), "Number of internal variables mismatch")
}

func TestConvertPKToRaw(t *testing.T) {
	cs := loadConstraints(t, "multiplier2.r1cs")
	pk, _ := loadKeys(t, "multiplier2_final.zkey", cs)

	var buffer bytes.Buffer

	_, err := pk.WriteRawTo(&buffer)
	require.NoError(t, err)

	readPk := groth16.NewProvingKey(ecc.BN254)
	_, err = readPk.UnsafeReadFrom(&buffer)
	require.NoError(t, err)

	require.Equal(t, pk.NbG1(), readPk.NbG1(), "Number of G1 elements mismatch")
	require.Equal(t, pk.NbG2(), readPk.NbG2(), "Number of G2 elements mismatch")
}

func TestConvertPKToDump(t *testing.T) {
	cs := loadConstraints(t, "multiplier2.r1cs")
	pk, _ := loadKeys(t, "multiplier2_final.zkey", cs)

	var buffer bytes.Buffer

	err := pk.WriteDump(&buffer)
	require.NoError(t, err)

	readPk := groth16.NewProvingKey(ecc.BN254)
	err = readPk.ReadDump(&buffer)
	require.NoError(t, err)

	require.Equal(t, pk.NbG1(), readPk.NbG1(), "Number of G1 elements mismatch")
	require.Equal(t, pk.NbG2(), readPk.NbG2(), "Number of G2 elements mismatch")
}
