#!/usr/bin/env python

import pathlib
import subprocess
import sys

from livereload import Server


def doxygen():
    doxyfile = pathlib.Path('docs/Doxyfile')
    content = doxyfile.read_text()
    content = content.replace('${INPUT}', '../risc0')
    content = content.replace('${OUTPUT_DIRECTORY}', '')
    content = content.replace('${WARN_AS_ERROR}', 'NO')
    tmp = pathlib.Path('tmp')
    tmp.mkdir(exist_ok=True)
    doxyfile = tmp / 'Doxyfile'
    doxyfile.write_text(content)
    doxygen = pathlib.Path(sys.prefix) / 'bin' / 'doxygen'
    subprocess.run([doxygen, doxyfile.resolve()], cwd='docs')

def rebuild():
    doxygen()

def main():
    rebuild()
    server = Server()
    server.watch('risc0/', rebuild)
    server.watch('docs/Doxyfile', rebuild)
    server.serve(root='docs/html')

if __name__ == "__main__":
    main()
