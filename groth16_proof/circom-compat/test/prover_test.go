package test

import (
	"circom-compat/internal/utils"
	"circom-compat/pkg/circom"
	"github.com/consensys/gnark/backend/groth16"
	"github.com/consensys/gnark/backend/witness"
	"github.com/consensys/gnark/constraint"
	"github.com/stretchr/testify/require"
	"path/filepath"
	"testing"
)

const DataFolder = "data"

// loadConstraints is a helper function to load and return a constraint system.
func loadConstraints(t *testing.T, r1csFile string) constraint.ConstraintSystem {
	t.Helper()
	file, err := utils.OpenBufferedFile(filepath.Join(DataFolder, r1csFile))
	require.NoError(t, err, "Failed to open R1CS file")
	defer file.Close()

	ccs, err := circom.ReadR1CS(file)
	require.NoError(t, err, "Failed to read R1CS file")

	return ccs
}

// loadKeys is a helper function to load and return a proving key and verifier key.
func loadKeys(t *testing.T, zkeyFile string, cs constraint.ConstraintSystem) (groth16.ProvingKey, groth16.VerifyingKey) {
	t.Helper()
	file, err := utils.OpenBufferedFile(filepath.Join(DataFolder, zkeyFile))
	require.NoError(t, err, "Failed to open zKey file")
	defer file.Close()

	pk, vk, err := circom.ReadZKey(file, cs)
	require.NoError(t, err, "Failed to read zKey file")

	return pk, vk
}

// Integration test verifying the proof using precompiled r1cs, zkey and wtns file.
func TestProof(t *testing.T) {
	// 1. Read the R1CS file
	cs := loadConstraints(t, "multiplier2.r1cs")

	// 2. Read the proving and verifying keys
	pk, vk := loadKeys(t, "multiplier2_final.zkey", cs)

	// 3. Read the full witness
	fullWitness := func() witness.Witness {
		file, err := utils.OpenBufferedFile(filepath.Join(DataFolder, "multiplier2.wtns"))
		require.NoError(t, err)
		defer file.Close()

		w, err := circom.ReadWTNS(file, cs)
		require.NoError(t, err)

		return w
	}()

	// 4. Create the proof.
	proof, err := groth16.Prove(cs, pk, fullWitness)
	require.NoError(t, err)

	// 5. Extract the public witness
	publicWitness, err := fullWitness.Public()
	require.NoError(t, err)

	// 6. Verify the proof
	require.NoError(t, groth16.Verify(proof, vk, publicWitness))
}
