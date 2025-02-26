# STARK by Hand - Interactive Jupyter Notebook

This project is an interactive version of the "STARK by Hand" guide in Jupyter Notebook format. It is designed to help developers and researchers better understand the mechanics of building STARK (Scalable Transparent ARgument of Knowledge).

## Structure

The notebook is divided into 12 lessons corresponding to the original guide:

1. Execution Trace
2. Rule Checks to Validate a Computation
3. Padding the Trace
4. Constructing Trace Polynomials
5. ZK Commitments of the Trace Data
6. Constraint Polynomials
7. Mixing Constraint Polynomials
8. The Core of the RISC Zero STARK
9. The DEEP Technique
10. Mixing for FRI
11. FRI Protocol (Commit Phase)
12. FRI Protocol (Query Phase)

## Installation

1. Create a Python virtual environment:
```bash
python -m venv venv
source venv/bin/activate  # for Linux/Mac
# or
venv\Scripts\activate  # for Windows
```

2. Install dependencies:
```bash
pip install -r requirements.txt
```

3. Start Jupyter Notebook:
```bash
jupyter notebook
```

## Requirements

See `requirements.txt` for the list of required Python packages.

## License

This project is distributed under the same license as the main RISC Zero project. 
