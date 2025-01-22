F = GF(97)
R.<x> = F[]

columns = [
    [24, 30, 54, 84, 78, 15, 29, 50],
    [30, 54, 84, 41, 2, 77, 21, 36],
    [54, 84, 41, 28, 71, 17, 92, 33],
    [1, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0, 0, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 0]
]

# root of unity
w = F(28)

# in this tutorial we always evaluate 32 rows (after the Reed-Solomon expansion of degree 4) so I hardcoded it
# also the shift to make the trace zero-knowledge is always `5` (in this tutorial), so let's hardcode it
def evaluate(polynomial, is_zk = False):
    shift = 5 if is_zk else 1
    return [polynomial(shift * pow(w, i)) for i in range(32)]

# interpolate polys
trace_polynomials = []
for col in columns:
    points = [(F(pow(w, i * 4)), v) for (i,v) in enumerate(col)]
    P = R.lagrange_polynomial(points)
    trace_polynomials.append(P)

# 4: reed solomon
columns_extended = []
for p in trace_polynomials:
    columns_extended.append(evaluate(p))

# 5: ZK -> we shift the evaluation domain
columns_zk = []
for p in trace_polynomials:
    columns_zk.append(evaluate(p, True))

# 6: constraint polynomials
constraint_polys = [
    (trace_polynomials[2] - trace_polynomials[1] - trace_polynomials[0]) * (trace_polynomials[3] + trace_polynomials[4] + trace_polynomials[5]),
    (trace_polynomials[0] - 24) * trace_polynomials[3],
    (trace_polynomials[1] - 30) * trace_polynomials[3],
    (trace_polynomials[2] - 28) * trace_polynomials[5],
    (trace_polynomials[0] - trace_polynomials[1](x * F(pow(28, -4)))) * trace_polynomials[4],
    (trace_polynomials[1] - trace_polynomials[2](x * F(pow(28, -4)))) * trace_polynomials[4],
]
constraint_columns = []
constraint_columns_zk = []
for p in constraint_polys:
    constraint_columns.append(evaluate(p))
    constraint_columns_zk.append(evaluate(p, True))

# 7: mix the constraints
alpha = F(3) # random
C = sum(pow(alpha, i) * p for (i,p) in enumerate(constraint_polys))

# 8: vanishing poly
Z = prod(x - F(pow(pow(5, 12), i)) for i in range(1, 9))

V = C // Z
# print("V: ", V)
# print("REST:", C % Z) # must be 0

# 9: DEEP
z = F(93) # random

deep_d1 = (trace_polynomials[0] - trace_polynomials[0](z)) / (x - z)
deep_c1 = (trace_polynomials[3] - trace_polynomials[3](z)) / (x - z)
deep_c2 = (trace_polynomials[4] - trace_polynomials[4](z)) / (x - z)
deep_c3 = (trace_polynomials[5] - trace_polynomials[5](z)) / (x - z)
deep_v = (V - V(z)) / (x - z)

# we choose `a` as the "previous clock input"
# in the initial trace (before reed-solomon), the inputs are 5^12, 5^24, ... or 28^4, 28^8, ...
# the previously chosen (random) value `z` is 93. If we want the "corresponding" value from the previous clock cycle,
# we can multiply by 5^-12, or 28^-4
a = z * pow(w, -4) # == 6

d2 = trace_polynomials[1]
d2bar = R.lagrange_polynomial([(a, d2(a)), (z, d2(z))])
deep_d2 = (d2 - d2bar) / ((x-z)*(x-a))

d3 = trace_polynomials[2]
d3bar = R.lagrange_polynomial([(a, d3(a)), (z, d3(z))])
deep_d3 = (d3 - d3bar) / ((x-z)*(x-a))

# 10: DEEP mixing
alpha2 = F(21) # random
deep_polys = [deep_d1, deep_d2, deep_d3, deep_c1, deep_c2, deep_c3, deep_v]
f = R(sum(pow(alpha2, i) * p for (i,p) in enumerate(deep_polys)))
print(f)
f_trace = evaluate(f, True)
# f_trace = [53,69,63,30,46,13,60,50,38,3,95,23,75,39,62,19,62,58,41,67,89,41,50,24,95,90,72,20,82,33,0,16]
f_points = [(pow(w,i), v) for (i,v) in enumerate(f_trace)]
f0 = R.lagrange_polynomial(f_points)
print(f0) # 10*x^6 + 37*x^5 + 43*x^4 + 48*x^3 + 34*x^2 + 56*x + 19

# f is the polynomial over the "zk domain"
# but we want it over the "normal" domain
f0 = f(x * F(pow(5,1)))
print(f0)

# # 11: FRI
# def split_polynomial(poly):
#     x = poly.parent().gen()
#     coeffs = poly.coefficients(sparse=False)
#     deg = poly.degree()
#     Pe = R(sum(coeffs[i] * x^(i//2) for i in range(0, deg + 1, 2)))
#     Po = R(sum(coeffs[i] * x^((i-1)//2) for i in range(1, deg + 1, 2)))
#     return Pe, Po

# def round(poly, alpha):
#     Pe, Po = split_polynomial(poly)
#     # print("Even part Pe(x):", Pe)   
#     # print("Odd part Po(x):", Po)
#     # print("Random challenge α:", alpha)
#     Pf = Pe + alpha * Po
#     # print("Folded polynomial Pf(x):", Pf)
#     return Pf

# f1 = round(f0, 12)
# f2 = round(f1, 32)
# f3 = round(f2, 64)