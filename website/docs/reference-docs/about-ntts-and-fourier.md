# About Number Theoretic Transforms

Number theoretic transforms (`NTTs`) and inverse number theoretic transforms (`iNTTs`) are a mechanism for converting between a `coefficient representation` and an `evaluation representation` of a given polynomial.

## Documentation

Implementation and documentation for NTTs and iNTTs is in the `risc0-zkp-core` [Rust crate](https://github.com/risc0/risc0#rust-crates).

## Basic Function

`NTTs` convert from `coefficient representation` to `evaluation representation`.

> `NTT(coefficients,field)=evaluations`

`iNTTs` convert from `evaluation representation` to `coefficient representation`

> `iNTT(evaluations,field)=coefficients`

## Background

NTTs are a [finite field](about-finite-fields.md) analog to Fourier transforms.
Fourier transforms, FFTs, DFTs and NTTs are various methods of transforming a function from **evaluation form** to **coefficient form**.

### Coefficient Form

An array $(a_0,a_1,\ldots,a_{n-1})$ defines a degree $n-1$ polynomial, $f$, where $f(x)=a_0x^0+a_1x^1+\ldots,a_{n-1}x^{n-1}$

### Evaluation Form

When an array is written in evaluation form, there's an implicit choice $g\in\mathbb{F}_q$.

> The powers of $g$ are used as an `indexing set` to form ordered pairs $(g^i,u_i)$.

The polynomial associated with the array $(u_0,u_1,\ldots,u_{n-1})$ is the unique polynomial $f$ such that the degree of $f$ is less than $n$ and $f(g^i)=u_i$.

## Suggested Reading and Videos

- [Slides](https://docs.google.com/presentation/d/18EMbRUihd8lUOMd1cIvqpCL1qI0JcCqp/edit?usp=sharing\&ouid=108906331404608387394\&rtpof=true\&sd=true) and [recording](https://youtu.be/Pct3rS4Y0IA) from RISC Zero Study Club.
- NTTs are just a finite field version of the FFT algorithm; to translate from FFTs to NTTs, replace the complex root of unity with a finite field root of unity.
  - This [DFT video](https://www.youtube.com/watch?v=nl9TZanwbBk) and [FFT video](https://www.youtube.com/watch?v=E8HeD-MUrjY) from UW professor Steve Brunton are brief and instructive.
  - [3blue1brown video](https://www.youtube.com/watch?v=spUNpyF58BY) and [lecture](https://www.youtube.com/watch?v=g8RkArhtCc4) on FFTs
  - [Veritasium](https://www.youtube.com/watch?v=nmgFG7PUHfo) on FFTs

For a deeper look into the algorithm at both a software and hardware level, we recommend this [FFT video from Reducible](https://www.youtube.com/watch?v=h7apO7q16V0). And here's [Vitalik's take](https://vitalik.eth.limo/general/2019/05/12/fft.html) on FFTs/NTTs.
