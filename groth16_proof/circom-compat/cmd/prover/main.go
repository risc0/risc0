package main

import (
	"circom-compat/internal/utils"
	"circom-compat/pkg/circom"
	circomjson "circom-compat/pkg/circom/json"
	"encoding/json"
	"errors"
	"flag"
	"fmt"
	"os"
	"path"
	"path/filepath"
	"time"

	"github.com/consensys/gnark-crypto/ecc"
	"github.com/consensys/gnark-crypto/ecc/bn254/fr"
	"github.com/consensys/gnark/backend/groth16"
	"github.com/consensys/gnark/backend/witness"
	"github.com/consensys/gnark/constraint"
	bn254r1cs "github.com/consensys/gnark/constraint/bn254"
	"github.com/consensys/gnark/logger"
)

func main() {
	flag.Parse()
	if flag.NArg() < 4 {
		help()
	}

	if err := run(); err != nil {
		if _, err := fmt.Fprintf(os.Stderr, "Error: %s\n", err); err != nil {
			panic(err)
		}
		os.Exit(1)
	}
}

func help() {
	programName := filepath.Base(os.Args[0])
	fmt.Printf("Usage of %s:\n", programName)
	fmt.Printf("\t<constraint file> <proving key file> <witness file> <output proof> [output public]\n")
	os.Exit(2)
}

func run() error {
	r1cs, err := loadCS(flag.Arg(0))
	if err != nil {
		return fmt.Errorf("failed to load constraint system: %w", err)
	}

	pk, err := loadPK(flag.Arg(1), r1cs)
	if err != nil {
		return fmt.Errorf("failed to load proving key: %w", err)
	}

	fullWitness, err := loadWitness(flag.Arg(2), r1cs)
	if err != nil {
		return fmt.Errorf("failed to load witness: %w", err)
	}

	proof, err := groth16.Prove(r1cs, pk, fullWitness)
	if err != nil {
		return fmt.Errorf("failed to create Groth16 proof: %w", err)
	}

	proofJSON, _ := json.Marshal(circomjson.NewProof(proof))
	if err := os.WriteFile(flag.Arg(3), proofJSON, 0644); err != nil {
		return fmt.Errorf("failed to write proof JSON: %w", err)
	}

	// write the public.json only when a forth argument is specified
	if publicFile := flag.Arg(4); len(publicFile) > 0 {
		sol, err := r1cs.Solve(fullWitness)
		if err != nil {
			panic(err)
		}
		wireValues := []fr.Element(sol.(*bn254r1cs.R1CSSolution).W)
		public := circomjson.NewPublic(wireValues[:r1cs.GetNbPublicVariables()])
		publicJSON, _ := json.Marshal(public)
		if err := os.WriteFile(publicFile, publicJSON, 0644); err != nil {
			return fmt.Errorf("failed to write public JSON: %w", err)
		}
	}

	return nil
}

func loadCS(name string) (constraint.ConstraintSystem, error) {
	log := logger.Logger()
	start := time.Now()

	file, err := utils.OpenBufferedFile(name)
	if err != nil {
		return nil, err
	}
	defer func() {
		if err := file.Close(); err != nil {
			log.Err(err).Msg("")
		}
	}()

	var cs constraint.ConstraintSystem
	switch utils.FullExt(name) {
	case "r1cs":
		cs, err = circom.ReadR1CS(file)
		if err != nil {
			return nil, err
		}
	case "cs":
		cs = groth16.NewCS(ecc.BN254)
		if _, err := cs.ReadFrom(file); err != nil {
			return nil, err
		}
	default:
		return nil, errors.New("invalid file format")
	}

	log.Debug().Dur("took", time.Since(start)).Msg("constraint system loaded")

	return cs, nil
}

func loadPK(name string, cs constraint.ConstraintSystem) (groth16.ProvingKey, error) {
	log := logger.Logger()
	start := time.Now()

	file, err := utils.OpenBufferedFile(name)
	if err != nil {
		return nil, err
	}
	defer func() {
		if err := file.Close(); err != nil {
			log.Err(err).Msg("")
		}
	}()

	var pk groth16.ProvingKey
	switch utils.FullExt(name) {
	case "zkey":
		pk, _, err = circom.ReadZKey(file, cs)
		if err != nil {
			return nil, err
		}
	case "pk":
		pk = groth16.NewProvingKey(ecc.BN254)
		if _, err := pk.UnsafeReadFrom(file); err != nil {
			return nil, err
		}
	case "pk.dmp":
		pk = groth16.NewProvingKey(ecc.BN254)
		if err := pk.ReadDump(file); err != nil {
			return nil, err
		}
	default:
		return nil, errors.New("invalid file format")
	}

	log.Debug().Dur("took", time.Since(start)).Msg("proving key loaded")

	return pk, nil
}

func loadWitness(name string, cs constraint.ConstraintSystem) (witness.Witness, error) {
	log := logger.Logger()
	start := time.Now()

	file, err := utils.OpenBufferedFile(name)
	if err != nil {
		return nil, err
	}
	defer func() {
		if err := file.Close(); err != nil {
			log.Err(err).Msg("")
		}
	}()

	var w witness.Witness
	switch path.Ext(name) {
	case ".wtns":
		w, err = circom.ReadWTNS(file, cs)
		if err != nil {
			return nil, err
		}
	default:
		return nil, errors.New("invalid file format")
	}

	log.Debug().Dur("took", time.Since(start)).Msg("witness data loaded")

	return w, nil
}
