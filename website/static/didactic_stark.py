from sympy import ntt, intt
import numpy as np
import galois

# Security Warning: The finite field arithmetic implemented in galois are not constant-time, but were instead designed for performance. As such, the library could be vulnerable to a side-channel timing attack. This library is not intended for production security, but instead for research & development, reverse engineering, cryptanalysis, experimentation, and general education.

# Preliminaries

# We use galois to define _finite_field_array. This functions like a numpy array, except
# that the array consists of elements of the finite field of size _field_size.
_field_size = 97
_finite_field_array = galois.GF(_field_size)
_primitive_root = _finite_field_array.primitive_element
_trace_length = 8
_reed_solomon_expansion_factor = 4
_block_length = _trace_length * _reed_solomon_expansion_factor
_generator = _primitive_root ** ((_field_size - 1) // _block_length)


# An EvaluationDomain is a collection of points on which to evaluate a polynomial
class EvaluationDomain:
    # Construct by directly providing the domain as an array
    def __init__(self, array):
        self.size = len(array)
        self.domain = array
        if self.size > 1:
            self.evaluation_domain_of_half_size = EvaluationDomain(
                [self.domain[2 * i] for i in range(self.size // 2)]
            )

    # Alternate constructor
    @classmethod
    def from_shift_generator_size(self, shift, generator, size):
        return EvaluationDomain(
            np.array([(shift * mod_pow(generator, i)) % _field_size for i in range(size)])
        )

    # Method to construct evaluation matrix for the given domain
    def as_vandermonde_matrix(self):
        self.evaluationmatrix = np.array(
            [
                [mod_pow(self.domain[j], i) for i in range(self.size)]
                for j in range(self.size)
            ]
        )
        return self.evaluationmatrix

    # Method to evaluate a given polynomial over the given domain
    def evaluate(self, coeffs):
        self.commitment = (
            self.as_vandermonde_matrix() @ extendarray(coeffs, self.size) % _field_size
        )
        return self.commitment

# A function that performs modular exponentiation
def mod_pow(base, exp):
   return pow(int(base), exp, _field_size)

# A function that returns the reciprocal modulo _field_size
def field_reciprocal(x):
    # By Fermat's Little Theorem, x^95 is the reciprocal of x (for non-zero x).
    x = _finite_field_array(x % _field_size)
    xinv = _finite_field_array(1) / x
    return xinv


# A function that returns an element-wise reciprocal of an array, modulo _field_size
def reciprocal_elementwise(array):
    return [field_reciprocal(x) for x in array]


# A function for extending a short array to a specified length:
def extendarray(short_array, length):
    size = len(short_array)
    # Validating short array is not too big:
    assert size <= length
    long_array = [0] * length
    # Write short_array contents into beginning of long_array:
    long_array[:size] = short_array[:size]
    return long_array


# A function that evaluates a polynomial at a given input
def evaluate_at_point(coeffs, x):
    # We evaluate f(x) as the dot product of [coefficients] and [powers]=[1, x, x^2, ...]
    powers = np.array([mod_pow(x, i) for i in range(len(coeffs))])
    eval = np.dot(coeffs, powers)
    return eval


# Define mix function for inside FRI
def mix(array, parameter):
    mixed_array = np.array([0] * len(array[0]))
    for i in range(len(array)):
        assert len(array[i]) == len(array[0])
        mixed_array = (
            mixed_array + (np.array(array[i]) * mod_pow(parameter,i))
        ) % _field_size
    return mixed_array


# Define quotient function for DEEP
def DEEPquotient(block, domain, testpoint, eval_testpoint):
    eval_quotient = (
        (block - eval_testpoint)
        * reciprocal_elementwise(domain - testpoint)
        % _field_size
    )
    return eval_quotient


# Define a function that splits a block into 2 blocks of half the length
def split(block, large_domain):
    small_domain = large_domain.evaluation_domain_of_half_size
    # Re-write block as a galois array
    block = _finite_field_array(block)
    evalmatrix_inv = np.linalg.inv(
        _finite_field_array(large_domain.as_vandermonde_matrix())
    )

    # Given a block u, we construct smaller blocks v_0, v_1

    # The defining relationship between u and v_i is easy to state in coefficient representation:
    #   Writing u_bar as the coefficient form of u, and v_bar_i as the coefficient form of v_i, we write:
    #   u_bar(x) = v_bar_0(x^2) + (x * v_bar_1(x^2))
    # We compute the coefficients of v_bar_0 and v_bar_1 through the following matrix multiplication:
    # _finite_field_array is the finite field of order _field_size:

    # Computing coefficient form of input:
    u_bar = evalmatrix_inv @ block

    # Writing coefficients of output polynomials:
    v_bar_0 = extendarray(
        [u_bar[2 * i] for i in range(len(u_bar) // 2)], len(small_domain.domain)
    )
    v_bar_1 = extendarray(
        [u_bar[1 + 2 * i] for i in range(len(u_bar) // 2)], len(small_domain.domain)
    )

    # Computing output blocks
    v_0 = small_domain.evaluate(v_bar_0)
    v_1 = small_domain.evaluate(v_bar_1)
    return [v_0, v_1]


def fri(block, input_domain, mixing_parameters, total_rounds, rounds_remaining):
    while rounds_remaining > 0:
        print("\n--- begin round", total_rounds - rounds_remaining + 1, "---")
        print("D_super_(", total_rounds - rounds_remaining, "):", input_domain.domain)
        split0, split1 = split(block, input_domain)
        next_domain = input_domain.evaluation_domain_of_half_size
        print("Split blocks: \n", split0, "\n", split1)
        print("Now mix those blocks using the mix parameter", mixing_parameters[0])
        round_commitment = mix([split0, split1], mixing_parameters[0])
        print(
            "FRI Commitment (aka f_super_(",
            total_rounds - rounds_remaining + 1,
            "):",
            round_commitment,
        )
        return fri(
            round_commitment,
            next_domain,
            mixing_parameters[1:],
            total_rounds,
            rounds_remaining - 1,
        )
    if rounds_remaining == 0:
        print("D_super_(", total_rounds - rounds_remaining, "):", input_domain.domain)
        return block


# Main ZKP Function:
def main():
    print("START \n")
    # A Didactic STARK
    # Proving computational integrity of a Fibonacci Program mod _field_size

    # We input 24 and 30 into a simple fibonacci program.
    # The inputs are loaded into d1_trace[0] and d2_trace[0]
    # We compute 4 rounds of fibonacci addition.
    # At each round, we write d3_trace[i] = d1_trace[i] + d2_trace[i]
    # After 4 rounds d3_trace[3] contains the output of the computation.

    # We claim that the following trace is a valid instantiation of this algorithm.
    # The trace is organized in columns, which are divided into two types: Data & Control.

    print("This is a Python implementation of the STARK by Hand Explainer.")
    print("https://dev.risczero.com/proof-system/stark-by-hand")
    print("")
    print("The Padded Execution Trace (See Lessons 1-3 in STARK by Hand)")
    # Trace: Data Columns
    d1_trace = np.array([24, 30, 54, 84, 78, 15, 29, 50])
    d2_trace = np.array([30, 54, 84, 41, 2, 77, 21, 36])
    d3_trace = np.array([54, 84, 41, 28, 71, 17, 92, 33])
    print("Trace Data Columns \n", d1_trace, "\n", d2_trace, "\n", d3_trace, "\n")

    # Trace: Control Columns
    # Init steps are flagged in c1_trace
    # Computation steps are flagged in c2_trace
    # Termination step is flagged in c3_trace
    # 0s at the end of each control column correspond to the padding of the trace
    c1_trace = np.array([1, 0, 0, 0, 0, 0, 0, 0])
    c2_trace = np.array([0, 1, 1, 1, 0, 0, 0, 0])
    c3_trace = np.array([0, 0, 0, 1, 0, 0, 0, 0])
    print("Trace Control Columns \n", c1_trace, "\n", c2_trace, "\n", c3_trace, "\n")
    trace_data = [d1_trace, d2_trace, d3_trace, c1_trace, c2_trace, c3_trace]

    # We will construct a zero-knowledge proof that:
    # this trace represents a program that satisfies these 6 rules:
    # 1) Fibonacci words here
    # 2) d1_trace[0] == 24  (init 1 constraint)
    # 3) d2_trace[0] == 30  (init 2 constraint)
    # 4) d3_trace[3] == 28  (termination constraint)
    # 5) if c2_trace[i] == 1, then d2_trace[i] == d1_trace[i+1]
    # 6) if c2_trace[i] == 1, then d3_trace[i] == d2_trace[i+1}

    print("Lesson 4: Constructing Trace Polynomials")
    # Trace Polynomials
    # We run an iNTT on each trace column to construct the associated trace polynomial
    d1_coeffs = np.array(intt(d1_trace, prime=_field_size))
    d2_coeffs = np.array(intt(d2_trace, prime=_field_size))
    d3_coeffs = np.array(intt(d3_trace, prime=_field_size))
    c1_coeffs = np.array(intt(c1_trace, prime=_field_size))
    c2_coeffs = np.array(intt(c2_trace, prime=_field_size))
    c3_coeffs = np.array(intt(c3_trace, prime=_field_size))
    print(
        "Coefficients of Trace Polynomials 1,2,...,6: \n",
        d1_coeffs,
        "\n",
        d2_coeffs,
        "\n",
        d3_coeffs,
        "\n",
        c1_coeffs,
        "\n",
        c2_coeffs,
        "\n",
        c3_coeffs,
        "\n",
    )

    # Evaluating Trace Polynomials over the powers of 5^12 would return the original trace data
    # Evaluating Trace Polynomials over the "expanded domain" gives a "trace block."
    expanded_domain = EvaluationDomain.from_shift_generator_size(1, 5**3, 32)
    d1_reedsolomonexpansion = expanded_domain.evaluate(d1_coeffs)
    d2_reedsolomonexpansion = expanded_domain.evaluate(d2_coeffs)
    d3_reedsolomonexpansion = expanded_domain.evaluate(d3_coeffs)
    c1_reedsolomonexpansion = expanded_domain.evaluate(c1_coeffs)
    c2_reedsolomonexpansion = expanded_domain.evaluate(c2_coeffs)
    c3_reedsolomonexpansion = expanded_domain.evaluate(c3_coeffs)
    print(
        "Reed Solomon Expansion of Trace Blocks: \n",
        d1_reedsolomonexpansion,
        "\n",
        d2_reedsolomonexpansion,
        "\n",
        d3_reedsolomonexpansion,
        "\n",
        c1_reedsolomonexpansion,
        "\n",
        c2_reedsolomonexpansion,
        "\n",
        c3_reedsolomonexpansion,
    )
    print("Note that every 4th entry matches the original trace data.")
    print("This is a degree 4 Reed Solomon expansion of the original trace. \n")
    trace_reedsolomonexpansion = np.array(
        [
            d1_reedsolomonexpansion,
            d2_reedsolomonexpansion,
            d3_reedsolomonexpansion,
            c1_reedsolomonexpansion,
            c2_reedsolomonexpansion,
            c3_reedsolomonexpansion,
        ]
    )

    print("Lesson 5: ZK Commitments of the Trace Data")
    print(
        'To maintain a zero-knowledge protocol, the trace polynomials are evaluated over a "zk commitment domain", {5^1, 5^4, ..., 5^94}.'
    )
    # Evaluating Trace Polynomials over the zk commitment domain gives "zero-knowledge trace blocks."
    zk_commitment_domain = EvaluationDomain.from_shift_generator_size(5, 5**3, 32)
    d1_zkcommitment = zk_commitment_domain.evaluate(d1_coeffs)
    d2_zkcommitment = zk_commitment_domain.evaluate(d2_coeffs)
    d3_zkcommitment = zk_commitment_domain.evaluate(d3_coeffs)
    c1_zkcommitment = zk_commitment_domain.evaluate(c1_coeffs)
    c2_zkcommitment = zk_commitment_domain.evaluate(c2_coeffs)
    c3_zkcommitment = zk_commitment_domain.evaluate(c3_coeffs)
    print(
        "Zero-Knowledge Trace Blocks: \n",
        d1_zkcommitment,
        "\n",
        d2_zkcommitment,
        "\n",
        d3_zkcommitment,
        "\n",
        c1_zkcommitment,
        "\n",
        c2_zkcommitment,
        "\n",
        c3_zkcommitment,
    )
    print(
        "These zk-commitment blocks do not share any evaluation points with the original trace data."
    )
    print(
        "These evaluations are committed to Merkle Trees (one for the data blocks and one for the control blocks."
    )
    print(
        'The term "polynomial commitment" describes this process of a Merkle commitment where the leaves of the tree are evaluations of a polynomial. \n'
    )
    print(
        "The root of these two Merkle Trees are the first entries on the RISC Zero seal."
    )
    print(
        "The third entry on the RISC Zero seal is a `Accum` commitment; that commitment is not necessary in this simplified example. \n"
    )
    trace_zkcommitment = np.array(
        [
            d1_zkcommitment,
            d2_zkcommitment,
            d3_zkcommitment,
            c1_zkcommitment,
            c2_zkcommitment,
            c3_zkcommitment,
        ]
    )

    print("Lesson 6: Constraint Polynomials")
    print(
        "The constraints are used to check the correctness of the trace. In this example, we check 6 rules to establish the validity of the trace."
    )

    # Applying rule checks to trace blocks makes constraint blocks.
    # A constraint block has 0s in every 4th row -- these 0s indicate the passing of the various rulechecks.

    # Applying rule checks to zk-commitment trace blocks makes zk-commitment constraint blocks.
    # Similarly, applying rule checks to trace polynomials makes constraint polynomials.
    # In code, this happens in terms of trace blocks.

    def fib_constraint(trace):
        # trace[2] - trace[1] - trace[0] returns 0 when the fibonacci addition relation holds.
        # trace[3] + trace[4] + trace[5] returns 0 when we aren't enforcing this rule.
        # The product of these two terms returns 0 at each row of the original trace.
        constraint = (
            np.multiply(
                (trace[2] - trace[1] - trace[0]), trace[3] + trace[4] + trace[5]
            )
            % _field_size
        )
        return constraint

    fib_constraint_columns = fib_constraint(trace_data)
    fib_constraint_reedsolomonexpansion = fib_constraint(trace_reedsolomonexpansion)
    fib_constraint_zkcommitment = fib_constraint(trace_zkcommitment)

    print(
        "Applied to the original trace data, the constraint yields all 0s: \n",
        fib_constraint_columns,
    )
    print(
        "Applied to the Reed-Solomon expanded trace blocks, the constraint yields 0s in every 4th row: \n",
        fib_constraint_reedsolomonexpansion,
    )
    print(
        "In practice, we apply these rule-checks to the trace blocks (i.e., the evaluations of the trace polynomials over the zk-commitment domain)."
    )
    print(
        "Although the zeros are no longer apparent, this block still corresponds to the evaluation of a polynomial whose degree is bounded by 2l where l is the length of the trace."
    )
    print(
        "The 6 constraint blocks and the associated polynomials and the coefficients of the associated polynomials are shown below: \n"
    )

    def init1_constraint(trace):
        # trace[0] - 24 returns 0 when the value loaded into the program matches the asserted input of 24
        # trace[3] returns 0 when we aren't enforcing this rule.
        # The product of these two terms returns 0 at each row of the original trace.
        constraint = np.multiply(trace[0] - 24, trace[3]) % _field_size
        return constraint

    init1_constraint_columns = init1_constraint(trace_data)
    init1_constraint_reedsolomonexpansion = init1_constraint(trace_reedsolomonexpansion)
    init1_constraint_zkcommitment = init1_constraint(trace_zkcommitment)

    def init2_constraint(trace):
        # trace[1] - 30 returns 0 when the value loaded into the program matches the asserted input of 30
        # trace[3] returns 0 when we aren't enforcing this rule.
        # The product of these two terms returns 0 at each row of the original trace.
        constraint = np.multiply(trace[1] - 30, trace[3]) % _field_size
        return constraint

    init2_constraint_columns = init2_constraint(trace_data)
    init2_constraint_reedsolomonexpansion = init2_constraint(trace_reedsolomonexpansion)
    init2_constraint_zkcommitment = init2_constraint(trace_zkcommitment)

    def termination_constraint(trace):
        # trace[2] - 28 returns 0 when the value loaded into the program matches the asserted input of 30
        # trace[5] returns 0 when we aren't enforcing this rule.
        # The product of these two terms returns 0 at each row of the original trace.
        constraint = np.multiply(trace[2] - 28, trace[5]) % _field_size
        return constraint

    termination_constraint_columns = termination_constraint(trace_data)
    termination_constraint_reedsolomonexpansion = termination_constraint(
        trace_reedsolomonexpansion
    )
    termination_constraint_zkcommitment = termination_constraint(trace_zkcommitment)

    def first_recursion_constraint(trace):
        # We check that the ith term in trace[0] matches the "previous" term in trace[1].
        # We use "previous" to mean "one computational step before."
        # i.e., for trace_columns, we're checking trace[0][i] against trace[0][i-1], while
        # for trace_zkcommitment and trace_reedsolomonexpansion, we're checking trace[0][i] vs. trace[1][i-4]
        # We express this length-dependent step-size as len(trace[0])//8
        # We also use "previous" in a cyclical sense, wrapping around to the end of the trace.
        # Putting this together, the relation we are checking is:
        #   trace[0][i] - trace[1][i - len(trace[0])//8 % len(trace[0])
        # trace[4] is the associated indicator column; trace[4][i] = 0 when this rule isn't enforced.
        constraint = np.zeros(len(trace[0]), int)
        for i in range(len(trace[0])):
            constraint[i] = (
                (trace[0][i] - trace[1][i - len(trace[0]) // 8 % len(trace[0])])
                * trace[4][i]
            ) % _field_size
            constraint = np.array(constraint)
        return constraint

    first_recursion_constraint_columns = first_recursion_constraint(trace_data)
    first_recursion_constraint_reedsolomonexpansion = first_recursion_constraint(
        trace_reedsolomonexpansion
    )
    first_recursion_constraint_zkcommitment = first_recursion_constraint(
        trace_zkcommitment
    )

    def second_recursion_constraint(trace):
        # We check that the ith term in trace[1] matches the "previous" term in trace[2].
        # See first_recursion_constraint for explanation of "previous."
        # trace[4] is the associated indicator column; trace[4][i] = 0 when this rule isn't enforced.
        constraint = np.zeros(len(trace[0]), int)
        for i in range(len(trace[0])):
            constraint[i] = (
                (trace[1][i] - trace[2][i - len(trace[0]) // 8 % len(trace[0])])
                * trace[4][i]
            ) % _field_size
            constraint = np.array(constraint)
        return constraint

    second_recursion_constraint_columns = second_recursion_constraint(trace_data)
    second_recursion_constraint_reedsolomonexpansion = second_recursion_constraint(
        trace_reedsolomonexpansion
    )
    second_recursion_constraint_zkcommitment = second_recursion_constraint(
        trace_zkcommitment
    )

    print("Constraint Blocks:")
    print("Fib Constraint: \n", fib_constraint_zkcommitment)
    print("Init1 Constraint: \n", init1_constraint_zkcommitment)
    print("Init2 Constraint: \n", init2_constraint_zkcommitment)
    print("Termination Constraint: \n", termination_constraint_zkcommitment)
    print("First Recursion Constraint: \n", first_recursion_constraint_zkcommitment)
    print(
        "Second Recursion Constraint: \n",
        second_recursion_constraint_zkcommitment,
        "\n",
    )

    print("Lesson 7: Mixing Constraint Polynomials")
    # We mix the constraint polynomials into a single mixed constraint polynomial.
    # In practice, this is a mix of evaluations over the zk-commitment domain.
    # For clarity, we show the Mixed Constraint Polynomial as evaluations over the same three domains as above.
    mixed_constraint_poly_columns = mix(
        [
            fib_constraint_columns,
            init1_constraint_columns,
            init2_constraint_columns,
            termination_constraint_columns,
            first_recursion_constraint_columns,
            second_recursion_constraint_columns,
        ],
        3,
    )
    mixed_constraint_poly_reedsolomonexpansion = mix(
        [
            fib_constraint_reedsolomonexpansion,
            init1_constraint_reedsolomonexpansion,
            init2_constraint_reedsolomonexpansion,
            termination_constraint_reedsolomonexpansion,
            first_recursion_constraint_reedsolomonexpansion,
            second_recursion_constraint_reedsolomonexpansion,
        ],
        3,
    )
    mixed_constraint_poly_zkcommitment = mix(
        [
            fib_constraint_zkcommitment,
            init1_constraint_zkcommitment,
            init2_constraint_zkcommitment,
            termination_constraint_zkcommitment,
            first_recursion_constraint_zkcommitment,
            second_recursion_constraint_zkcommitment,
        ],
        3,
    )

    print(
        "Although they stay in evaluation form throughout the protocol, we show the constraint polynomials in coefficient form for didactic clarity and trouble-shooting. To convert between coefficient form and evaluation form of a given polynomial, we use iNTTs and NTTs. \n"
    )
    # Computing coefficients of Constraint Polynomials:
    fib_constraintPoly_coeffs = intt(
        fib_constraint_reedsolomonexpansion, prime=_field_size
    )
    init1_constraintPoly_coeffs = intt(
        init1_constraint_reedsolomonexpansion, prime=_field_size
    )
    init2_constraintPoly_coeffs = intt(
        init2_constraint_reedsolomonexpansion, prime=_field_size
    )
    termination_constraintPoly_coeffs = intt(
        termination_constraint_reedsolomonexpansion, prime=_field_size
    )
    first_recursion_constraintPoly_coeffs = intt(
        first_recursion_constraint_reedsolomonexpansion, prime=_field_size
    )
    second_recursion_constraintPoly_coeffs = intt(
        second_recursion_constraint_reedsolomonexpansion, prime=_field_size
    )
    mixed_constraint_poly_coeffs = intt(
        mixed_constraint_poly_reedsolomonexpansion, prime=_field_size
    )

    print("Coefficients of Constraint Polynomials:")
    print("Fibonacci Constraint: ", fib_constraintPoly_coeffs)
    print("Init1 Constraint: ", init1_constraintPoly_coeffs)
    print("Init2 Constraint: ", init2_constraintPoly_coeffs)
    print("Termination Constraint: ", termination_constraintPoly_coeffs)
    print("First Recursion Constraint: ", first_recursion_constraintPoly_coeffs)
    print("Second Recursion Constraint: ", second_recursion_constraintPoly_coeffs, "\n")
    print("Mixed Constraint Coefficients: \n", mixed_constraint_poly_coeffs, "\n")

    print(
        "We now introduce the Zeros Polynomial, which is used to compute the Validity Polynomial."
    )
    # The Zeros Polynomial is Z(x) = x^8 - 1
    # Remember the "difference of perfect squares" from Algebra II?
    # It turns out that this "difference of perfect 8th powers" works out very nicely over finite fields.
    # Z(x) = (x - 5^0)(x - 5^12)(x - 5^24)...(x-5^84)
    # The next term in the pattern would be (x-5^96), which "wraps around" quite nicely since 5^0 = 5^96.
    zeros_poly_coeffs = [-1, 0, 0, 0, 0, 0, 0, 0, 1]
    zeros_poly_evals_reedsolomonexpansion = expanded_domain.evaluate(zeros_poly_coeffs)
    zeros_poly_evals_zkcommitment = zk_commitment_domain.evaluate(zeros_poly_coeffs)
    print("Zeros Polynomial coefficients: \n", zeros_poly_coeffs)
    print(
        "Zeros Polynomial evaluated on Reed Solomon expansion domain: \n",
        zeros_poly_evals_reedsolomonexpansion,
    )
    print(
        "Zeros Polynomial evaluated on zk-commitment domain: \n",
        zeros_poly_evals_zkcommitment,
        "\n",
    )

    # Constructing reciprocals of Zeros Polynomial evals to facilitate computation
    reciprocals_of_zeros_poly = reciprocal_elementwise(zeros_poly_evals_zkcommitment)

    print("Lesson 8: The core of the RISC Zero STARK")
    # Constructing Validity Polynomial
    print(
        "The Validity Polynomial is the quotient of the Mixed Constraint Polynomial and the Zeros Polynomial."
    )
    validity_polynomial_evals = (
        np.multiply(mixed_constraint_poly_zkcommitment, reciprocals_of_zeros_poly)
        % _field_size
    )
    print(
        "Evaluations of Validity Polynomial on zk-commitment domain \n",
        validity_polynomial_evals,
        "\n",
    )
    print(
        "These evaluations are committed to a Merkle tree, and the root of that tree is appended to the seal."
    )
    print(
        "The rest of the protocol aims to prove that the commitments for the trace polynomials and the validity polynomials are actually evaluations of low-degree polynomials that satisfy V=C/Z as asserted. \n"
    )
    # Constructing coefficients of validity polynomial for use in DEEP
    evalmatrix_inv = np.linalg.inv(
        _finite_field_array(zk_commitment_domain.as_vandermonde_matrix())
    )
    validity_polynomial_coeffs = np.array(
        evalmatrix_inv @ _finite_field_array(validity_polynomial_evals)
    )

    print("Lesson 9: The DEEP Technique")
    print(
        "The DEEP technique is a means of improving the security level associated with a single query by sampling from a larger domain than the commitment domain."
    )
    DEEP_test_point = 93
    print(
        "The prover provides information to convince the verifier that the Merkle commitments satisfy the relation V=C/Z at the DEEP_test_point,",
        DEEP_test_point,
        "\n",
    )

    # The DEEP Polynomials all share the following denominator.
    DEEPdenom = (zk_commitment_domain.domain - DEEP_test_point) % _field_size

    # We rewrite DEEPdenom in terms of reciprocals to facilitate computation later:
    DEEPdenom = reciprocal_elementwise(DEEPdenom)

    # TODO: Implement Interpolation of taps for DEEP_poly2 & DEEP_poly3

    DEEP_poly1_evals = DEEPquotient(
        d1_zkcommitment,
        zk_commitment_domain.domain,
        DEEP_test_point,
        evaluate_at_point(d1_coeffs, DEEP_test_point),
    )
    # DEEP_poly2 = hard-coded for now
    # DEEP Poly 3 = hard-coded for now
    DEEP_poly4_evals = DEEPquotient(
        c1_zkcommitment,
        zk_commitment_domain.domain,
        DEEP_test_point,
        evaluate_at_point(c1_coeffs, DEEP_test_point),
    )
    DEEP_poly5_evals = DEEPquotient(
        c2_zkcommitment,
        zk_commitment_domain.domain,
        DEEP_test_point,
        evaluate_at_point(c2_coeffs, DEEP_test_point),
    )
    DEEP_poly6_evals = DEEPquotient(
        c3_zkcommitment,
        zk_commitment_domain.domain,
        DEEP_test_point,
        evaluate_at_point(c3_coeffs, DEEP_test_point),
    )
    DEEPValidity_evals = DEEPquotient(
        validity_polynomial_evals,
        zk_commitment_domain.domain,
        DEEP_test_point,
        evaluate_at_point(validity_polynomial_coeffs, DEEP_test_point),
    )
    print("##")
    # Hard-coding DEEP Polynomial evaluations for now
    DEEP_poly2_evals = [
        19,
        74,
        82,
        13,
        48,
        30,
        17,
        58,
        93,
        63,
        64,
        42,
        45,
        10,
        21,
        71,
        1,
        52,
        72,
        71,
        60,
        10,
        8,
        44,
        41,
        5,
        14,
        16,
        49,
        15,
        78,
        41,
    ]

    # Hard-coding DEEP Polynomial evaluations for now
    DEEP_poly3_evals = [
        84,
        63,
        89,
        93,
        75,
        36,
        11,
        80,
        44,
        23,
        40,
        11,
        80,
        33,
        38,
        50,
        72,
        33,
        35,
        78,
        8,
        8,
        86,
        36,
        9,
        25,
        88,
        95,
        65,
        22,
        50,
        91,
    ]

    print("Interpolation of DEEP Poly 1:\n", intt(DEEP_poly1_evals, _field_size))
    print("Interpolations of DEEP_poly2: \n", intt(DEEP_poly2_evals, _field_size))
    print("Interpolations of DEEP_poly3: \n", intt(DEEP_poly3_evals, _field_size))
    print("interpolation of DEEP poly 4: \n", intt(DEEP_poly4_evals, _field_size))
    print("interpolation of DEEP poly 5:\n", intt(DEEP_poly5_evals, _field_size))
    print("interpolation of DEEP poly 6:\n", intt(DEEP_poly6_evals, _field_size))
    print(
        "interpolation of DEEP Validity Polynomial:\n",
        intt(DEEPValidity_evals, _field_size),
    )

    print("Lesson 10: Mixing (Batching) for FRI")
    print("The initial FRI polynomial is the mix of the 7 DEEP polynomials.")
    fri_input = mix(
        [
            DEEP_poly1_evals,
            DEEP_poly2_evals,
            DEEP_poly3_evals,
            DEEP_poly4_evals,
            DEEP_poly5_evals,
            DEEP_poly6_evals,
            DEEPValidity_evals,
        ],
        21,
    )

    print("Interpolation of initial FRI Input")
    print(intt(fri_input, _field_size))
    print("With the `batching` complete, we're ready for the FRI commit rounds: \n")

    print("Lesson 11: FRI Commit Rounds")
    print(
        "In this part of the protocol, the prover provides information to convince the verifier that the DEEP polynomials are low-degree."
    )
    print("It follows that the Trace & Validity polynomials are also low-degree. \n")

    mixingparameters_fri = np.array([1, 3, 22])
    num_rounds = 3
    assert num_rounds == len(mixingparameters_fri)

    # Run (num_rounds) rounds of FRI commit
    print("FRI Commit Phase")
    final_fri_block = EvaluationDomain(
        fri(
            fri_input,
            zk_commitment_domain,
            mixingparameters_fri,
            num_rounds,
            num_rounds,
        )
    ).evaluation_domain_of_half_size.domain
    print("The Prover sends this final FRI Commitment in full, rather than as a hash.")
    print(
        "The Verifier can confirm manually that the final FRI commitment is indeed a low-degree polynomial."
    )
    print("")
    print("Lesson 12: FRI Query Phase")
    print(
        "The FRI Query phase confirms the correctness of the folding at each round of the FRI commit phase."
    )
    print(
        "In the Batched FRI protocol, the query phase also checks the correctness of the FRI batching."
    )

    print(
        "We only show a single query, and we only instantiate the check for the final round of FRI folding."
    )
    print(
        "Future improvements may extend this to include a more complete implementation of FRI queries."
    )

    print(
        "The notation here matches what's described on page 39 of Proximity Gaps for Reed-Solomon Codes."
    )
    print(
        "For a more complete description of the query phase, see https://eprint.iacr.org/2020/654"
    )
    print("")

    # Specifying query location
    print("The verifier specifies a query location g_super_(3) from D_super_(3)")
    g_super_3_index = 25
    g_super_3 = mod_pow(5, g_super_3_index)
    print("Choose g_super_(3) = 5^{} = {}.\n".format(g_super_3_index, g_super_3))

    print("Now, the prover provides 2 evaluations from f_super_(2).")
    print(
        "The verifier will use these evaluations to confirm the purported value of f_super_(3)."
    )
    print("The details here are rather hairy:")
    print("")

    # Query location determines coset
    print("The choice of g_super_3 determines a coset C_super_2.")
    print(
        "C_super_(2) = {{ g : g/5 is a square root of (g_super_3)/5 }} = {{ 5^{}, 5^{} }}".format(
            (g_super_3_index - 1) // 2 + 1,
            (g_super_3_index - 1) // 2 + (_field_size + 1) // 2,
        )
    )
    C_super_2 = EvaluationDomain(
        [
            mod_pow(5, ((g_super_3_index - 1) // 2 + 1)),
            mod_pow(5, ((g_super_3_index - 1) // 2 + (_field_size + 1) // 2)),
        ]
    )
    print("")

    print(
        "The prover provides the evaluations of f_super_2 on each of the elements of C_super_2."
    )
    print("")

    print("The coset C_super_2 determines a Vandermonde Matrix M_super_2")
    M_super_2 = np.linalg.inv(_finite_field_array(C_super_2.as_vandermonde_matrix()))
    print("M_super_2 = inversevandermonde(C_super_2) = \n", M_super_2)
    print("")

    # boldface_z_super_2 is the vector of powers of the mixing parameters
    boldface_z_super_2 = EvaluationDomain([1, mixingparameters_fri[2]])

    # Checking folding
    # See page 39 of Proximity Gaps for RS Codes
    expected = np.dot(
        _finite_field_array(boldface_z_super_2.domain),
        (M_super_2 @ _finite_field_array(final_fri_block)),
    )
    # Reject if f_super_3 evaluated @ g_super_(3) != expected

    print(
        "Now, the verifier can use the check shown in step (3) of `A single invocation of the batched QUERY phase.`"
    )
    print(
        "Check the source code or page 39 of the ProxGaps paper to see a detailed description of this check."
    )

    print(
        "The verifier computes an `expected` value for f_super_(3) evaluated at g_super_(3)"
    )
    print("and checks the result against the purported value provided earlier.")

    print(
        "This check confirms the correctness of the folding from f_super_2 to f_super_3."
    )
    print(
        "A more complete demonstration of a FRI query would include an analogous check to confirm"
    )
    print(
        "the correctness of each round of FRI folding, and a check to confirm the initial FRI batching."
    )
    print("")
    print("Congratulations!")
    print(
        "You've just run a (mostly) complete STARK protocol, including DEEP-ALI, FRI committing, and a FRI query."
    )
    print("")
    print(
        "For a more visual & more verbose walk-through of this example, check out our STARK by Hand explainer:"
    )
    print("https://dev.risczero.com/proof-system/stark-by-hand")
    print("")
    print(
        "We also have videos at https://dev.risczero.com/studyclub that walk through a large portion of these ideas."
    )
    print("")
    print("We hope you find these resources useful -- happy learning!")
    print("Got questions/feedback? Find us on Discord: https://discord.gg/risczero")
    print("")


if __name__ == "__main__":
    main()
