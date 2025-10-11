package main

import (
	"bytes"
	"circom-compat/internal/utils"
	"circom-compat/pkg/circom"
	"compress/gzip"
	"flag"
	"fmt"
	"io"
	"os"
	"path"
	"path/filepath"
	"strings"

	"github.com/consensys/gnark/backend/groth16"
	"github.com/consensys/gnark/constraint"
)

var dumpPK = flag.Bool("dump", false, "use very unsafe memory dump to serialize the proving key")

func main() {
	flag.Parse()
	if flag.NArg() < 2 {
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
	fmt.Printf("\t<r1cs file> <zkey file>\n")
	os.Exit(2)
}

func run() error {
	r1csFile, zkeyFile := flag.Arg(0), flag.Arg(1)

	cs, err := loadCS(r1csFile)
	if err != nil {
		return fmt.Errorf("failed to load r1cs file: %w", err)
	}

	pk, err := loadPK(zkeyFile, cs)
	if err != nil {
		return fmt.Errorf("failed to load zkey file: %w", err)
	}

	r1csFile = strings.TrimSuffix(r1csFile, ".gz")
	csFile := strings.TrimSuffix(r1csFile, path.Ext(r1csFile)) + ".cs"
	if err := utils.WriteToBufferedFile(csFile, cs.WriteTo); err != nil {
		return fmt.Errorf("failed to write constraint system: %w", err)
	}

	zkeyFile = strings.TrimSuffix(zkeyFile, ".gz")
	pkFile := strings.TrimSuffix(zkeyFile, path.Ext(zkeyFile)) + ".pk"
	write := pk.WriteRawTo
	if *dumpPK {
		write = dumpWriter(pk)
		pkFile += ".dmp"
	}
	if err := utils.WriteToBufferedFile(pkFile, write); err != nil {
		return fmt.Errorf("failed to write proving key: %w", err)
	}

	return nil
}

func loadCS(name string) (constraint.ConstraintSystem, error) {
	file, err := utils.OpenBufferedFile(name)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	if !strings.HasSuffix(name, ".gz") {
		return circom.ReadR1CS(file)
	}

	gz, err := gzip.NewReader(file)
	if err != nil {
		return nil, err
	}
	cs, err := circom.ReadR1CS(gz)
	if err != nil {
		return nil, err
	}

	return cs, gz.Close()
}

func loadPK(name string, cs constraint.ConstraintSystem) (groth16.ProvingKey, error) {
	file, err := utils.OpenBufferedFile(name)
	if err != nil {
		return nil, err
	}
	defer file.Close()

	if !strings.HasSuffix(name, ".gz") {
		pk, _, err := circom.ReadZKey(file, cs)
		return pk, err
	}

	gz, err := gzip.NewReader(file)
	if err != nil {
		return nil, err
	}
	pk, _, err := circom.ReadZKey(gz, cs)
	if err != nil {
		return nil, err
	}

	return pk, gz.Close()
}

func dumpWriter(pk groth16.ProvingKey) utils.WriteFunc {
	return func(w io.Writer) (int64, error) {
		var buf bytes.Buffer
		if err := pk.WriteDump(&buf); err != nil {
			return 0, err
		}
		n, err := w.Write(buf.Bytes())
		return int64(n), err
	}
}
