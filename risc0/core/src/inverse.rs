// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use alloc::{vec, vec::Vec};
use core::cmp::min;

use crate::field::Elem;

struct ExtensionField<T> {
    degree: usize,
    irreducible: Vec<T>,
}

impl<T: Elem> ExtensionField<T> {
    fn new(degree: usize, irreducible: Vec<T>) -> Self {
        Self {
            degree,
            irreducible,
        }
    }

    fn zero(&self) -> Vec<T> {
        vec![T::ZERO; self.degree]
    }

    fn one(&self) -> Vec<T> {
        let mut coeffs = vec![T::ZERO; self.degree];
        coeffs[0] = T::ONE;
        coeffs
    }

    fn sub(&self, a: &[T], b: &[T]) -> Vec<T> {
        let mut c = a.to_vec();
        c.resize(self.degree, T::ZERO);
        for i in 0..min(self.degree, b.len()) {
            c[i] -= b[i];
        }
        c
    }

    // fn mul(&self, a: &[T], b: &[T]) -> Vec<T> {
    //     let mut c = self.naive_mul(a, b);

    //     // Reduce the degree using the irreducible polynomial
    //     let upper = 2 * self.degree - 2;
    //     for i in (self.degree..=upper).rev() {
    //         let x = c[i];
    //         for j in 0..self.degree {
    //             c[i - self.degree] += x * self.irreducible[j];
    //         }
    //         c[i] = T::ZERO;
    //     }
    //     c.truncate(self.degree);
    //     c
    // }

    fn mul_elem(&self, a: T, b: &[T]) -> Vec<T> {
        let mut c = self.zero();
        for i in 0..self.degree {
            c[i] = a * b[i];
        }
        c
    }

    fn inv(&self, a: &[T]) -> Vec<T> {
        let f = ExtensionField::new(self.degree + 1, self.irreducible.clone());
        let mut t0 = f.zero();
        let mut t1 = f.one();
        let mut r0 = self.irreducible.clone();
        let mut r1 = a.to_vec();

        while Self::degree(&r1) > 0 {
            let quot = self.div(&r0, &r1);
            let r2 = f.sub(&r0, &f.naive_mul(&quot, &r1));
            r0 = r1;
            r1 = r2;
            let t2 = f.sub(&t0, &f.naive_mul(&quot, &t1));
            t0 = t1;
            t1 = t2;
        }

        self.mul_elem(r1[0].inv(), &t1)
    }

    fn div(&self, a: &[T], b: &[T]) -> Vec<T> {
        let a_degree = Self::degree(a);
        let b_degree = Self::degree(b);

        // Work in an extension field that can fit this extension field's irreducible
        // polynomial. This is necessary because `a` will be the irreducible polynomial
        // in the first step of Euclid's algorithm for finding multiplicative inverses.
        let f = ExtensionField::new(self.degree + 1, self.irreducible.clone());
        let mut b2 = f.zero();
        let mut r = f.zero();
        let mut q = f.zero();
        for i in 0..=a_degree {
            r[i] = a[i];
        }
        for i in 0..=b_degree {
            b2[i] = b[i];
        }

        let mut r_degree = a_degree;
        while r_degree >= b_degree {
            debug_assert_eq!(q[r_degree - b_degree], T::ZERO);
            q[r_degree - b_degree] = r[r_degree] * b2[b_degree].inv();

            r = f.sub(a, &f.naive_mul(&q, &b2));
            r_degree = Self::degree(&r);
        }

        q
    }

    fn naive_mul(&self, a: &[T], b: &[T]) -> Vec<T> {
        let mut c = vec![T::ZERO; 2 * self.degree - 1];
        for i in 0..a.len() {
            for j in 0..b.len() {
                c[i + j] += a[i] * b[j];
            }
        }
        c
    }

    fn degree(x: &[T]) -> usize {
        match x.iter().skip(1).rev().position(|x| *x != T::ZERO) {
            Some(i) => x.len() - 1 - i,
            None => 0,
        }
    }
}

pub fn inv<T: Elem>(a: &[T], irreducible: Vec<T>) -> Vec<T> {
    ExtensionField::new(a.len(), irreducible).inv(a)
}
