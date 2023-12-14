#![allow(clippy::many_single_char_names)]
#![allow(clippy::op_ref)]

use std::{
    fs,
    fs::File,
    io::{BufReader, BufWriter, Read, Write},
};
use rmp_serde;
use halo2_core::VerifierComponents;

use ff::{FromUniformBytes, WithSmallOrderMulGroup};
use halo2_proofs::arithmetic::Field;
use halo2_proofs::circuit::{Cell, Layouter, SimpleFloorPlanner, Value};
use halo2_proofs::dev::MockProver;
use halo2_proofs::plonk::{
    create_proof as create_plonk_proof, keygen_pk, keygen_vk, verify_proof as verify_plonk_proof,
    Advice, Assigned, Circuit, Column, ConstraintSystem, Error, Fixed, ProvingKey, TableColumn,
    VerifyingKey,
};
use halo2_proofs::poly::commitment::{CommitmentScheme, Params, ParamsProver, Prover, Verifier};
use halo2_proofs::poly::Rotation;
use halo2_proofs::poly::VerificationStrategy;
use halo2_proofs::transcript::{
    Blake2bRead, Blake2bWrite, Challenge255, EncodedChallenge, TranscriptReadBuffer,
    TranscriptWriterBuffer,
};

use halo2_proofs::poly::kzg::commitment::{KZGCommitmentScheme, ParamsKZG};
use halo2_proofs::poly::kzg::multiopen::{ProverGWC, VerifierGWC};
use halo2_proofs::poly::kzg::strategy::AccumulatorStrategy;
use halo2_proofs::SerdeFormat;
use halo2curves::bn256::Bn256;
use halo2curves::bn256::G1Affine;
use halo2curves::bn256::Fr;

use rand_core::{OsRng, RngCore};
use std::marker::PhantomData;

const K: u32 = 5;

/// This represents an advice column at a certain row in the ConstraintSystem
#[derive(Copy, Clone, Debug)]
pub struct Variable(Column<Advice>, usize);

#[derive(Clone)]
struct PlonkConfig {
    a: Column<Advice>,
    b: Column<Advice>,
    c: Column<Advice>,
    d: Column<Advice>,
    e: Column<Advice>,

    sa: Column<Fixed>,
    sb: Column<Fixed>,
    sc: Column<Fixed>,
    sm: Column<Fixed>,
    sp: Column<Fixed>,
    sl: TableColumn,
}

#[allow(clippy::type_complexity)]
trait StandardCs<FF: Field> {
    fn raw_multiply<F>(
        &self,
        layouter: &mut impl Layouter<FF>,
        f: F,
    ) -> Result<(Cell, Cell, Cell), Error>
    where
        F: FnMut() -> Value<(Assigned<FF>, Assigned<FF>, Assigned<FF>)>;
    fn raw_add<F>(
        &self,
        layouter: &mut impl Layouter<FF>,
        f: F,
    ) -> Result<(Cell, Cell, Cell), Error>
    where
        F: FnMut() -> Value<(Assigned<FF>, Assigned<FF>, Assigned<FF>)>;
    fn copy(&self, layouter: &mut impl Layouter<FF>, a: Cell, b: Cell) -> Result<(), Error>;
    fn public_input<F>(&self, layouter: &mut impl Layouter<FF>, f: F) -> Result<Cell, Error>
    where
        F: FnMut() -> Value<FF>;
    fn lookup_table(&self, layouter: &mut impl Layouter<FF>, values: &[FF]) -> Result<(), Error>;
}

#[derive(Clone)]
struct MyCircuit<F: Field> {
    a: Value<F>,
    lookup_table: Vec<F>,
}

struct StandardPlonk<F: Field> {
    config: PlonkConfig,
    _marker: PhantomData<F>,
}

impl<FF: Field> StandardPlonk<FF> {
    fn new(config: PlonkConfig) -> Self {
        StandardPlonk {
            config,
            _marker: PhantomData,
        }
    }
}

impl<FF: Field> StandardCs<FF> for StandardPlonk<FF> {
    fn raw_multiply<F>(
        &self,
        layouter: &mut impl Layouter<FF>,
        mut f: F,
    ) -> Result<(Cell, Cell, Cell), Error>
    where
        F: FnMut() -> Value<(Assigned<FF>, Assigned<FF>, Assigned<FF>)>,
    {
        layouter.assign_region(
            || "raw_multiply",
            |mut region| {
                let mut value = None;
                let lhs = region.assign_advice(
                    || "lhs",
                    self.config.a,
                    0,
                    || {
                        value = Some(f());
                        value.unwrap().map(|v| v.0)
                    },
                )?;
                region.assign_advice(
                    || "lhs^4",
                    self.config.d,
                    0,
                    || value.unwrap().map(|v| v.0).square().square(),
                )?;
                let rhs = region.assign_advice(
                    || "rhs",
                    self.config.b,
                    0,
                    || value.unwrap().map(|v| v.1),
                )?;
                region.assign_advice(
                    || "rhs^4",
                    self.config.e,
                    0,
                    || value.unwrap().map(|v| v.1).square().square(),
                )?;
                let out = region.assign_advice(
                    || "out",
                    self.config.c,
                    0,
                    || value.unwrap().map(|v| v.2),
                )?;

                region.assign_fixed(|| "a", self.config.sa, 0, || Value::known(FF::ZERO))?;
                region.assign_fixed(|| "b", self.config.sb, 0, || Value::known(FF::ZERO))?;
                region.assign_fixed(|| "c", self.config.sc, 0, || Value::known(FF::ONE))?;
                region.assign_fixed(|| "a * b", self.config.sm, 0, || Value::known(FF::ONE))?;
                Ok((lhs.cell(), rhs.cell(), out.cell()))
            },
        )
    }
    fn raw_add<F>(
        &self,
        layouter: &mut impl Layouter<FF>,
        mut f: F,
    ) -> Result<(Cell, Cell, Cell), Error>
    where
        F: FnMut() -> Value<(Assigned<FF>, Assigned<FF>, Assigned<FF>)>,
    {
        layouter.assign_region(
            || "raw_add",
            |mut region| {
                let mut value = None;
                let lhs = region.assign_advice(
                    || "lhs",
                    self.config.a,
                    0,
                    || {
                        value = Some(f());
                        value.unwrap().map(|v| v.0)
                    },
                )?;
                region.assign_advice(
                    || "lhs^4",
                    self.config.d,
                    0,
                    || value.unwrap().map(|v| v.0).square().square(),
                )?;
                let rhs = region.assign_advice(
                    || "rhs",
                    self.config.b,
                    0,
                    || value.unwrap().map(|v| v.1),
                )?;
                region.assign_advice(
                    || "rhs^4",
                    self.config.e,
                    0,
                    || value.unwrap().map(|v| v.1).square().square(),
                )?;
                let out = region.assign_advice(
                    || "out",
                    self.config.c,
                    0,
                    || value.unwrap().map(|v| v.2),
                )?;

                region.assign_fixed(|| "a", self.config.sa, 0, || Value::known(FF::ONE))?;
                region.assign_fixed(|| "b", self.config.sb, 0, || Value::known(FF::ONE))?;
                region.assign_fixed(|| "c", self.config.sc, 0, || Value::known(FF::ONE))?;
                region.assign_fixed(|| "a * b", self.config.sm, 0, || Value::known(FF::ZERO))?;
                Ok((lhs.cell(), rhs.cell(), out.cell()))
            },
        )
    }
    fn copy(&self, layouter: &mut impl Layouter<FF>, left: Cell, right: Cell) -> Result<(), Error> {
        layouter.assign_region(
            || "copy",
            |mut region| {
                region.constrain_equal(left, right)?;
                region.constrain_equal(left, right)
            },
        )
    }
    fn public_input<F>(&self, layouter: &mut impl Layouter<FF>, mut f: F) -> Result<Cell, Error>
    where
        F: FnMut() -> Value<FF>,
    {
        layouter.assign_region(
            || "public_input",
            |mut region| {
                let value = region.assign_advice(|| "value", self.config.a, 0, &mut f)?;
                region.assign_fixed(|| "public", self.config.sp, 0, || Value::known(FF::ONE))?;

                Ok(value.cell())
            },
        )
    }
    fn lookup_table(&self, layouter: &mut impl Layouter<FF>, values: &[FF]) -> Result<(), Error> {
        layouter.assign_table(
            || "",
            |mut table| {
                for (index, &value) in values.iter().enumerate() {
                    table.assign_cell(
                        || "table col",
                        self.config.sl,
                        index,
                        || Value::known(value),
                    )?;
                }
                Ok(())
            },
        )?;
        Ok(())
    }
}

impl<F: Field> Circuit<F> for MyCircuit<F> {
    type Config = PlonkConfig;
    type FloorPlanner = SimpleFloorPlanner;
    #[cfg(feature = "circuit-params")]
    type Params = ();

    fn without_witnesses(&self) -> Self {
        Self {
            a: Value::unknown(),
            lookup_table: self.lookup_table.clone(),
        }
    }

    fn configure(meta: &mut ConstraintSystem<F>) -> PlonkConfig {
        let e = meta.advice_column();
        let a = meta.advice_column();
        let b = meta.advice_column();
        let sf = meta.fixed_column();
        let c = meta.advice_column();
        let d = meta.advice_column();
        let p = meta.instance_column();

        meta.enable_equality(a);
        meta.enable_equality(b);
        meta.enable_equality(c);

        let sm = meta.fixed_column();
        let sa = meta.fixed_column();
        let sb = meta.fixed_column();
        let sc = meta.fixed_column();
        let sp = meta.fixed_column();
        let sl = meta.lookup_table_column();

        /*
         *   A         B      ...  sl
         * [
         *   instance  0      ...  0
         *   a         a      ...  0
         *   a         a^2    ...  0
         *   a         a      ...  0
         *   a         a^2    ...  0
         *   ...       ...    ...  ...
         *   ...       ...    ...  instance
         *   ...       ...    ...  a
         *   ...       ...    ...  a
         *   ...       ...    ...  0
         * ]
         */

        meta.lookup("lookup", |meta| {
            let a_ = meta.query_any(a, Rotation::cur());
            vec![(a_, sl)]
        });

        meta.create_gate("Combined add-mult", |meta| {
            let d = meta.query_advice(d, Rotation::next());
            let a = meta.query_advice(a, Rotation::cur());
            let sf = meta.query_fixed(sf, Rotation::cur());
            let e = meta.query_advice(e, Rotation::prev());
            let b = meta.query_advice(b, Rotation::cur());
            let c = meta.query_advice(c, Rotation::cur());

            let sa = meta.query_fixed(sa, Rotation::cur());
            let sb = meta.query_fixed(sb, Rotation::cur());
            let sc = meta.query_fixed(sc, Rotation::cur());
            let sm = meta.query_fixed(sm, Rotation::cur());

            vec![a.clone() * sa + b.clone() * sb + a * b * sm - (c * sc) + sf * (d * e)]
        });

        meta.create_gate("Public input", |meta| {
            let a = meta.query_advice(a, Rotation::cur());
            let p = meta.query_instance(p, Rotation::cur());
            let sp = meta.query_fixed(sp, Rotation::cur());

            vec![sp * (a - p)]
        });

        meta.enable_equality(sf);
        meta.enable_equality(e);
        meta.enable_equality(d);
        meta.enable_equality(p);
        meta.enable_equality(sm);
        meta.enable_equality(sa);
        meta.enable_equality(sb);
        meta.enable_equality(sc);
        meta.enable_equality(sp);

        PlonkConfig {
            a,
            b,
            c,
            d,
            e,
            sa,
            sb,
            sc,
            sm,
            sp,
            sl,
        }
    }

    fn synthesize(&self, config: PlonkConfig, mut layouter: impl Layouter<F>) -> Result<(), Error> {
        let cs = StandardPlonk::new(config);

        let _ = cs.public_input(&mut layouter, || Value::known(F::ONE + F::ONE))?;

        for _ in 0..10 {
            let a: Value<Assigned<_>> = self.a.into();
            let mut a_squared = Value::unknown();
            let (a0, _, c0) = cs.raw_multiply(&mut layouter, || {
                a_squared = a.square();
                a.zip(a_squared).map(|(a, a_squared)| (a, a, a_squared))
            })?;
            let (a1, b1, _) = cs.raw_add(&mut layouter, || {
                let fin = a_squared + a;
                a.zip(a_squared)
                    .zip(fin)
                    .map(|((a, a_squared), fin)| (a, a_squared, fin))
            })?;
            cs.copy(&mut layouter, a0, a1)?;
            cs.copy(&mut layouter, b1, c0)?;
        }

        cs.lookup_table(&mut layouter, &self.lookup_table)?;

        Ok(())
    }
}

macro_rules! common {
    ($scheme:ident) => {{
        let a = <$scheme as CommitmentScheme>::Scalar::from(2834758237)
            * <$scheme as CommitmentScheme>::Scalar::ZETA;
        let instance =
            <$scheme as CommitmentScheme>::Scalar::ONE + <$scheme as CommitmentScheme>::Scalar::ONE;
        let lookup_table = vec![instance, a, a, <$scheme as CommitmentScheme>::Scalar::ZERO];
        (a, instance, lookup_table)
    }};
}

fn keygen<Scheme: CommitmentScheme>(params: &Scheme::ParamsProver) -> ProvingKey<Scheme::Curve>
where
    Scheme::Scalar: FromUniformBytes<64> + WithSmallOrderMulGroup<3>,
{
    let (_, _, lookup_table) = common!(Scheme);
    let empty_circuit: MyCircuit<Scheme::Scalar> = MyCircuit {
        a: Value::unknown(),
        lookup_table,
    };

    // Initialize the proving key
    let vk = keygen_vk(params, &empty_circuit).expect("keygen_vk should not fail");

    keygen_pk(params, vk, &empty_circuit).expect("keygen_pk should not fail")
}

fn create_proof<
    'params,
    Scheme: CommitmentScheme,
    P: Prover<'params, Scheme>,
    E: EncodedChallenge<Scheme::Curve>,
    R: RngCore,
    T: TranscriptWriterBuffer<Vec<u8>, Scheme::Curve, E>,
>(
    rng: R,
    params: &'params Scheme::ParamsProver,
    pk: &ProvingKey<Scheme::Curve>,
) -> Vec<u8>
where
    Scheme::Scalar: Ord + WithSmallOrderMulGroup<3> + FromUniformBytes<64>,
{
    let (a, instance, lookup_table) = common!(Scheme);

    let circuit: MyCircuit<Scheme::Scalar> = MyCircuit {
        a: Value::known(a),
        lookup_table,
    };

    let mut transcript = T::init(vec![]);

    create_plonk_proof::<Scheme, P, _, _, _, _>(
        params,
        pk,
        &[circuit.clone(), circuit.clone()],
        &[&[&[instance]], &[&[instance]]],
        rng,
        &mut transcript,
    )
    .expect("proof generation should not fail");

    // Check this circuit is satisfied.
    let prover = match MockProver::run(K, &circuit, vec![vec![instance]]) {
        Ok(prover) => prover,
        Err(e) => panic!("{:?}", e),
    };
    assert_eq!(prover.verify(), Ok(()));

    transcript.finalize()
}

fn verify_proof<
    'a,
    'params,
    Scheme: CommitmentScheme,
    V: Verifier<'params, Scheme>,
    E: EncodedChallenge<Scheme::Curve>,
    T: TranscriptReadBuffer<&'a [u8], Scheme::Curve, E>,
    Strategy: VerificationStrategy<'params, Scheme, V, Output = Strategy>,
>(
    params_verifier: &'params Scheme::ParamsVerifier,
    vk: &VerifyingKey<Scheme::Curve>,
    proof: &'a [u8],
) where
    Scheme::Scalar: Ord + WithSmallOrderMulGroup<3> + FromUniformBytes<64>,
{
    let (_, instance, _) = common!(Scheme);
    let pubinputs = [instance];

    let mut transcript = T::init(proof);

    let strategy = Strategy::new(params_verifier);
    let strategy = verify_plonk_proof(
        params_verifier,
        vk,
        strategy,
        &[&[&pubinputs[..]], &[&pubinputs[..]]],
        &mut transcript,
    )
    .unwrap();

    assert!(strategy.finalize());
}

fn main() {
    //type Scheme = KZGCommitmentScheme<Bn256>;

    // Generate the SRS
    let params = ParamsKZG::<Bn256>::new(K);
    let rng = OsRng;

    // Generate a proving key
    let pk = keygen::<KZGCommitmentScheme<_>>(&params);

    // Create the proof
    let proof = create_proof::<_, ProverGWC<_>, _, _, Blake2bWrite<_, _, Challenge255<_>>>(
        rng, &params, &pk,
    );

    // Generate the verifier params
    let verifier_params = params.verifier_params();

    // Generate the verifier key
    let vk = pk.get_vk();

    // Now we can test verification works using the three generated parameters
    verify_proof::<_, VerifierGWC<_>, _, Blake2bRead<_, _, Challenge255<_>>, AccumulatorStrategy<_>>(
        verifier_params,
        vk,
        &proof[..],
    );

    // Serialize the params to bytes
    let mut params_bytes = vec![];
    let _ = <ParamsKZG<_> as Params<_>>::write(&verifier_params, &mut params_bytes);

    // Serialize the verifier key into bytes
    let vk_bytes = vk.to_bytes(SerdeFormat::RawBytes);

    // Now we can enter these byte arrays into our VerifyComponents Struct, which is defined in the core folder
    let verfier_components = VerifierComponents {
        v_params: params_bytes,
        vk: vk_bytes,
        proof: proof,
    };

    // Serialize the struct and save it to in the res folder
    let serialized_struct = rmp_serde::to_vec(&verfier_components).unwrap();
    let mut f = File::create("../res/verification.components").unwrap();
    f.write_all(&serialized_struct).expect("REASON");

    // As a sanity check, we can deserialize the file and re-run the Halo2 verification function
    let mut f1 = File::open("../res/verification.components").expect("No file found");
    let mut verification_buffer = Vec::new();
    f1.read_to_end(&mut verification_buffer)
        .expect("unable to read data");

    let deserialized_struct: VerifierComponents = rmp_serde::from_slice(&verification_buffer).unwrap();

    let v_params_bytes = deserialized_struct.v_params;
    let vk_bytes = deserialized_struct.vk;
    let des_proof = deserialized_struct.proof;

    // Deserialize the params_bytes into a ParamsKZG<Bn256> struct
    let des_verifier_params: ParamsKZG<Bn256> = Params::read::<_>(&mut &v_params_bytes[..]).unwrap();

    // Deserialize the vk_bytes into a verfying key struct
    //let des_vk = VerifyingKey::<G1Affine>::from_bytes::<?>(&vk_bytes, SerdeFormat::RawBytes, #[cfg(feature = "circuit-params")] des_verifier_params).unwrap();

    #[allow(clippy::unit_arg)]
    let des_vk = VerifyingKey::<G1Affine>::from_bytes::<MyCircuit<Fr>>(
        &vk_bytes,
        SerdeFormat::RawBytes,
        #[cfg(feature = "circuit-params")]
        des_verifier_params,
    )
    .unwrap();
    // Rerun the verification function
    verify_proof::<_, VerifierGWC<_>, _, Blake2bRead<_, _, Challenge255<_>>, AccumulatorStrategy<_>>(
        &des_verifier_params,
        &des_vk,
        &des_proof[..],
    );

    // alternative method for exporting param and vk files

    // let f = File::create("serialization-test.params").unwrap();
    // let mut writer = BufWriter::new(f);
    // params.write(&mut writer).unwrap();

    // let mut f2 = File::open("serialization-test.params").expect("No file found");
    // let metadata = fs::metadata("serialization-test.params").expect("unable to read metadata");
    // let mut verifier_params_buffer: Vec<u8> = vec![0; metadata.len() as usize];
    // f2.read(&mut verifier_params_buffer).expect("buffer overflow");
}
