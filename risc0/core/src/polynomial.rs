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

pub(crate) struct ExtensionField<T> {
    degree: usize,
    irreducible: Vec<T>,
}

impl<T: Elem> ExtensionField<T> {
    pub fn new(degree: usize, irreducible: Vec<T>) -> Self {
        Self {
            degree,
            irreducible,
        }
    }

    pub fn zero(&self) -> Vec<T> {
        vec![T::ZERO; self.degree]
    }

    pub fn one(&self) -> Vec<T> {
        let mut coeffs = vec![T::ZERO; self.degree];
        coeffs[0] = T::ONE;
        coeffs
    }

    pub fn sub(&self, a: &[T], b: &[T]) -> Vec<T> {
        let mut c = a.to_vec();
        c.resize(self.degree, T::ZERO);
        for i in 0..min(self.degree, b.len()) {
            c[i] -= b[i];
        }
        c
    }

    pub fn mul(&self, a: &[T], b: &[T]) -> Vec<T> {
        let mut c = self.naive_mul(a, b);

        // Reduce the degree using the irreducible polynomial
        let upper = 2 * self.degree - 2;
        for i in (self.degree..=upper).rev() {
            let x = c[i];
            for j in 0..self.degree {
                c[i - self.degree] += x * self.irreducible[j];
            }
            c[i] = T::ZERO;
        }
        c.truncate(self.degree);
        c
    }

    pub fn mul_elem(&self, a: T, b: &[T]) -> Vec<T> {
        let mut c = self.zero();
        for i in 0..self.degree {
            c[i] = a * b[i];
        }
        c
    }

    pub fn div(&self, a: &[T], b: &[T]) -> Vec<T> {
        let a_degree = degree(a);
        let b_degree = degree(b);

        // Work in an extension field that can fit this extension field's irreducible
        // polynomial. This is necessary because `a` will be the irreducible polynomial
        // in the first step of Euclid's algorithm for finding multiplicative inverses.
        let f = ExtensionField::new(self.degree + 1, self.irreducible.clone());
        let mut b2 = vec![T::ZERO; self.degree + 1];
        let mut r = vec![T::ZERO; self.degree + 1];
        let mut q = vec![T::ZERO; self.degree + 1];
        for i in 0..a_degree {
            r[i] = a[i];
        }
        for i in 0..b_degree {
            b2[i] = b[i];
        }

        let mut r_degree = a_degree;
        while r_degree >= a_degree {
            debug_assert_eq!(q[r_degree - b_degree], T::ZERO);
            q[r_degree - b_degree] = r[r_degree] * b2[b_degree].inv();
            r = f.sub(a, &f.naive_mul(&q, &b2));
            r_degree = degree(&r);
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
}

pub fn degree<T: Elem>(x: &[T]) -> usize {
    for i in (1..x.len()).rev() {
        if x[i] != T::ZERO {
            return i;
        }
    }
    0
}
