// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use sppark::NTTInputOutputOrder;

const DEFAULT_GPU: usize = 0;

#[test]
#[cfg(feature = "gl64")]
fn gl64_self_consistency() {
    use rand::random;

    fn random_fr() -> u64 {
        let fr: u64 = random();
        fr % 0xffffffff00000001
    }

    for lg_domain_size in 1..24 + 4 * !cfg!(debug_assertions) as i32 {
        let domain_size = 1usize << lg_domain_size;

        let v: Vec<u64> = (0..domain_size).map(|_| random_fr()).collect();

        let mut vtest1 = v.clone();
        let mut vtest2 = v.clone();

        ntt_cuda::NTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::NN);

        ntt_cuda::NTT(DEFAULT_GPU, &mut vtest2, NTTInputOutputOrder::RR);
        assert!(vtest1 == vtest2);

        ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::NN);

        ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest2, NTTInputOutputOrder::RR);
        assert!(v == vtest1);
        assert!(vtest1 == vtest2);

        ntt_cuda::NTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::NR);

        ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::RN);
        assert!(v == vtest1);
    }
}

#[test]
#[cfg(feature = "bb31")]
fn bb31_self_consistency() {
    use rand::random;

    fn random_fr() -> u32 {
        let fr: u32 = random();
        fr % 0x78000001
    }

    for lg_domain_size in 1..24 + 4 * !cfg!(debug_assertions) as i32 {
        let domain_size = 1usize << lg_domain_size;

        let v: Vec<u32> = (0..domain_size).map(|_| random_fr()).collect();

        let mut vtest1 = v.clone();
        let mut vtest2 = v.clone();

        ntt_cuda::NTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::NN);

        ntt_cuda::NTT(DEFAULT_GPU, &mut vtest2, NTTInputOutputOrder::RR);
        assert!(vtest1 == vtest2);

        ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::NN);

        ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest2, NTTInputOutputOrder::RR);
        assert!(v == vtest1);
        assert!(vtest1 == vtest2);

        ntt_cuda::NTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::NR);

        ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest1, NTTInputOutputOrder::RN);
        assert!(v == vtest1);
    }
}

#[cfg(any(
    feature = "bls12_377",
    feature = "bls12_381",
    feature = "bn254",
    feature = "pallas",
    feature = "vesta",
))]
#[test]
fn test_against_arkworks() {
    #[cfg(feature = "bls12_377")]
    use ark_bls12_377::Fr;
    #[cfg(feature = "bls12_381")]
    use ark_bls12_381::Fr;
    #[cfg(feature = "bn254")]
    use ark_bn254::Fr;
    #[cfg(feature = "pallas")]
    use ark_pallas::Fr;
    #[cfg(feature = "vesta")]
    use ark_vesta::Fr;
    use ark_ff::{PrimeField, UniformRand};
    use ark_poly::{
        domain::DomainCoeff, EvaluationDomain, GeneralEvaluationDomain,
    };
    use ark_std::test_rng;

    fn test_ntt<
        F: PrimeField,
        T: DomainCoeff<F> + UniformRand + core::fmt::Debug + Eq,
        R: ark_std::rand::Rng,
        D: EvaluationDomain<F>,
    >(
        rng: &mut R,
    ) {
        for lg_domain_size in 1..20 + 4 * !cfg!(debug_assertions) as i32 {
            let domain_size = 1usize << lg_domain_size;

            let domain = D::new(domain_size).unwrap();

            let mut v = vec![];
            for _ in 0..domain_size {
                v.push(T::rand(rng));
            }

            v.resize(domain.size(), T::zero());
            let mut vtest = v.clone();

            domain.fft_in_place(&mut v);
            ntt_cuda::NTT(DEFAULT_GPU, &mut vtest, NTTInputOutputOrder::NN);
            assert!(vtest == v);

            domain.ifft_in_place(&mut v);
            ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest, NTTInputOutputOrder::NN);
            assert!(vtest == v);

            ntt_cuda::NTT(DEFAULT_GPU, &mut vtest, NTTInputOutputOrder::NR);
            ntt_cuda::iNTT(DEFAULT_GPU, &mut vtest, NTTInputOutputOrder::RN);
            assert!(vtest == v);

            domain.coset_fft_in_place(&mut v);
            ntt_cuda::coset_NTT(DEFAULT_GPU, &mut vtest, NTTInputOutputOrder::NN);
            assert!(vtest == v);

            domain.coset_ifft_in_place(&mut v);
            ntt_cuda::coset_iNTT(DEFAULT_GPU, &mut vtest, NTTInputOutputOrder::NN);
            assert!(vtest == v);
        }
    }

    let rng = &mut test_rng();

    test_ntt::<Fr, Fr, _, GeneralEvaluationDomain<Fr>>(rng);
}
