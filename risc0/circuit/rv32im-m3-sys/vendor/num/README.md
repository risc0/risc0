# Num
Single file header only C++ implementation of BigInteger / BigNum / unlimited size integers and rational numbers

### Supported operations on `Num` type:

Artithmetic:
`+, -, *, /, +=, -=, *=, /=, %=`

Comparison:
`==, !=, <=, >=, <, >`

Bit ops:
`get_bit, set_bit, clr_bit`

Shifts:
`<<, >>, <<=, >>=`

Fancy stuff:
`gcd, sqrt, pow, mod_pow, div_mod`

Base conversion:
```cpp
Num a("539", 16);

std::vector<char> c;
a.print(c, 2);
puts(&c[0]); // 10100111001
```

For more examples, e.g. calculating digits of `Pi` and `e`, see `tests.cpp`.
