// Copyright 2022 Risc0, Inc.
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

use log::debug;
use risc0_zkp::core::fp4::Fp4;

pub fn ffpu_execute(code: &[u32], args: &mut [&mut [Fp4]]) {
    let mut regs = Vec::new();
    for word in code {
        let opcode = word & 0b11;
        let id = regs.len();
        match opcode {
            0b00 => {
                let index = ((word >> 16) & 0xffff) as usize;
                let bufid = ((word >> 8) & 0b11111) as usize;
                if ((word & 0b100) >> 2) == 0 {
                    // get
                    let local = (word >> 3) & 0b1;
                    if local == 1 {
                        debug!("%{id} = get(%{index})");
                        regs.push(regs[index]);
                    } else {
                        debug!("%{id} = get($0x{index:04x}, 0x{bufid:02x})");
                        regs.push(args[bufid][index]);
                    }
                } else {
                    // set
                    debug!("set($0x{index:04x}, 0x{bufid:02x})");
                    let buf = args.get_mut(bufid).unwrap();
                    buf[index] = regs[regs.len() - 1];
                }
            }
            0b01 => {
                // add
                let a = ((word >> 16) & 0xffff) as usize;
                let b = ((word >> 2) & 0x3fff) as usize;
                debug!("%{id} = add(%{a}, %{b})");
                regs.push(regs[a] + regs[b]);
            }
            0b10 => {
                // sub
                let a = ((word >> 16) & 0xffff) as usize;
                let b = ((word >> 2) & 0x3fff) as usize;
                debug!("%{id} = sub(%{a}, %{b})");
                regs.push(regs[a] - regs[b]);
            }
            0b11 => {
                // mul
                let a = ((word >> 16) & 0xffff) as usize;
                let b = ((word >> 2) & 0x3fff) as usize;
                debug!("%{id} = mul(%{a}, %{b})");
                regs.push(regs[a] * regs[b]);
            }
            _ => panic!("Illegal instruction"),
        }
    }
}

#[cfg(test)]
mod test {
    use risc0_zkp::core::{
        fp::Fp,
        fp4::Fp4,
        ntt::{bit_reverse, interpolate_ntt},
    };
    use risc0_zkp::field::Elem;
    use risc0_zkp::verify::ffpu::fold_eval::{CODE, DATA};

    use super::ffpu_execute;

    fn fold_eval_cpu_impl(values: &mut [Fp4], mix: Fp4, inv_wk: Fp) -> Fp4 {
        interpolate_ntt::<Fp, Fp4>(values);
        bit_reverse(values);
        poly_eval(values, mix, inv_wk)
    }

    fn poly_eval(coeffs: &[Fp4], x: Fp4, y: Fp) -> Fp4 {
        let mut mul_fp = Fp::ONE;
        let mut mul_fp4 = Fp4::ONE;
        let mut tot = Fp4::ZERO;
        for i in 0..coeffs.len() {
            tot += coeffs[i] * mul_fp * mul_fp4;
            mul_fp *= y;
            mul_fp4 *= x;
        }
        tot
    }

    #[test]
    fn fold_eval() {
        let mix = Fp4::from_u32_words(&[754974156, 235902752, 1509949422, 247234757]);
        let inv_wk = Fp::new(1750988476);

        let mut data: Vec<Fp4> = DATA.iter().map(|x| Fp4::from_u32(*x)).collect();
        let mut values = vec![
            Fp4::from_u32_words(&[1339902010, 1327050052, 741894090, 551985746]),
            Fp4::from_u32_words(&[1346610458, 1382415645, 779783418, 24633420]),
            Fp4::from_u32_words(&[1535085618, 850116638, 1758707259, 131986417]),
            Fp4::from_u32_words(&[474568498, 784097751, 1843748326, 1056379554]),
            Fp4::from_u32_words(&[771083500, 1379003367, 574752313, 1807794478]),
            Fp4::from_u32_words(&[703976897, 1500989690, 516679607, 1388295964]),
            Fp4::from_u32_words(&[483079525, 1929814310, 1381101540, 1360040706]),
            Fp4::from_u32_words(&[1773905316, 1767879717, 401472700, 286525323]),
            Fp4::from_u32_words(&[254446378, 1594297538, 545407522, 1382502752]),
            Fp4::from_u32_words(&[1490665615, 1058569656, 924718412, 1813503172]),
            Fp4::from_u32_words(&[1519564552, 338862258, 1620559784, 662359927]),
            Fp4::from_u32_words(&[1119844631, 809577467, 1297603444, 572281709]),
            Fp4::from_u32_words(&[1483367748, 36648671, 239111224, 1055671143]),
            Fp4::from_u32_words(&[84274338, 789489478, 1840007322, 1187120294]),
            Fp4::from_u32_words(&[759055459, 1200045003, 2001387588, 775691691]),
            Fp4::from_u32_words(&[1725644405, 532070615, 1731542348, 59211207]),
        ];

        let mut copy = values.clone();
        let mut out = [Fp4::default()];

        let mut args = [
            data.as_mut_slice(),
            copy.as_mut_slice(),
            &mut [mix],
            &mut [Fp4::from(inv_wk)],
            &mut out,
        ];
        ffpu_execute(&CODE, &mut args);

        let expected = fold_eval_cpu_impl(&mut values, mix, inv_wk);

        assert_eq!(out[0], expected);
    }
}
