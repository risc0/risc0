// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Polynomial utilities (currently only those used in polynomial evaluation).

use alloc::vec;

use risc0_core::field::ExtElem;

/// Evaluate a polynomial whose coefficients are in the extension field at a
/// point.
pub fn poly_eval<E: ExtElem>(coeffs: &[E], x: E) -> E {
    let mut mul = E::ONE;
    let mut tot = E::ZERO;
    for coeff in coeffs {
        tot += *coeff * mul;
        mul *= x;
    }
    tot
}

/// General purpose polynomial interpolation.
///
/// Given the goal value f(x) at a set of evaluation points x, compute
/// coefficients.
pub fn poly_interpolate<E: ExtElem>(out: &mut [E], x: &[E], fx: &[E], size: usize) {
    // Special case the very easy ones
    if size == 1 {
        out[0] = fx[0];
        return;
    }
    if size == 2 {
        out[1] = (fx[1] - fx[0]) * (x[1] - x[0]).inv();
        out[0] = fx[0] - out[1] * x[0];
        return;
    }
    // Compute ft = product of (x - x_i) for all i
    let mut ft = vec![E::ZERO; size + 1];
    ft[0] = E::ONE;
    for (i, x) in x.iter().enumerate().take(size) {
        for j in (0..i + 1).rev() {
            let value = ft[j];
            ft[j + 1] += value;
            ft[j] *= -*x;
        }
    }
    // Clear output
    for x in &mut *out {
        *x = E::ZERO;
    }
    for i in 0..size {
        // Compute fr = ft / (x - x_i)
        let mut fr = ft.clone();
        poly_divide(&mut fr, x[i]);
        // Evaluate at x[i]
        let fr_xi = poly_eval(&fr, x[i]);
        // Compute multiplier (fx[i] / fr_xi)
        let mul = fx[i] * fr_xi.inv();
        // Multiply into output
        for j in 0..size {
            out[j] += mul * fr[j];
        }
    }
}

/// In-place polynomial division.
///
/// Take the coefficients in P, and divide by (X - z) for some z, return the
/// remainder.
pub fn poly_divide<E: ExtElem>(p: &mut [E], z: E) -> E {
    let mut cur = E::ZERO;
    for i in (0..p.len()).rev() {
        let next = z * cur + p[i];
        p[i] = cur;
        cur = next;
    }
    cur
}
