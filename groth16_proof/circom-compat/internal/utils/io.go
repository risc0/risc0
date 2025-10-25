package utils

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"path"
	"strings"
)

// FullExt extracts the file extension from the given filename.
func FullExt(name string) string {
	_, file := path.Split(name)
	return file[strings.IndexRune(file, '.')+1:]
}

// WriteFunc is a function type that writes data to an io.Writer and returns the number of bytes written and any error.
type WriteFunc func(io.Writer) (int64, error)

// WriteToBufferedFile creates a new file with the given name and writes data to it using the provided WriteFunc with buffering.
func WriteToBufferedFile(name string, write WriteFunc) error {
	f, err := os.Create(name)
	if err != nil {
		return fmt.Errorf("failed to create file: %w", err)
	}
	defer f.Close()

	w := bufio.NewWriter(f)
	if _, err := write(w); err != nil {
		return fmt.Errorf("failed to write: %w", err)
	}
	if err := w.Flush(); err != nil {
		return fmt.Errorf("failed to flush: %w", err)
	}

	return nil
}

// OpenBufferedFile opens a file with the given name and returns a buffered io.ReadCloser.
func OpenBufferedFile(name string) (io.ReadCloser, error) {
	f, err := os.Open(name)
	if err != nil {
		return nil, fmt.Errorf("failed to open file: %w", err)
	}

	return &readCloser{bufio.NewReader(f), f}, nil
}

// readCloser combines an io.Reader and the underlying file
type readCloser struct {
	io.Reader
	f *os.File
}

// Close closes both the reader and the file
func (rc *readCloser) Close() error {
	return rc.f.Close()
}
