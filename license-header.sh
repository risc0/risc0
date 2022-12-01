#!/usr/bin/env bash

python license-header.py update --source 'risc0/**/*.cpp' --license LICENSE-header --line-before '//' --after ""
python license-header.py update --source 'risc0/**/*.h' --license LICENSE-header --line-before '//' --after ""
python license-header.py update --source 'risc0/**/*.rs' --license LICENSE-header --line-before '//' --after ""
