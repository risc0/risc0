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

extern crate alloc;

use alloc::{string::String, vec, vec::Vec};
use core::fmt;

use anyhow::{anyhow, Error, Result};
// TODO
use risc0_binfmt::{tagged_struct, Digestible};
use risc0_zkp::core::{digest::Digest, hash::sha::Sha256};
use serde::{ser::{SerializeSeq, SerializeStruct}, Deserialize, Serialize};

use crate::{from_u256, g1_from_bytes, g2_from_bytes, VerifyingKey};

/// Groth16 seal object encoded in big endian.
#[derive(Clone, Debug, Deserialize, Serialize, PartialEq)]
pub struct Seal {
    /// Proof 'a' value
    pub a: Vec<Vec<u8>>,
    /// Proof 'b' value
    pub b: Vec<Vec<Vec<u8>>>,
    /// Proof 'c' value
    pub c: Vec<Vec<u8>>,
}

impl Seal {
    const ELEMENT_SIZE: usize = 32;
    const G1_GROUP_SIZE: usize = Self::ELEMENT_SIZE * 2;
    const G2_GROUP_SIZE: usize = Self::ELEMENT_SIZE * 4;
    const SIZE: usize = Self::G1_GROUP_SIZE * 2 + Self::G2_GROUP_SIZE;

    /// Serialize the Groth16 `Seal` into a `Vec<u8>`
    pub fn to_vec(&self) -> Vec<u8> {
        let mut result = Vec::with_capacity(Self::SIZE);

        // Serialize 'a'
        for item in &self.a {
            result.extend(item);
        }

        // Serialize 'b'
        for sub_vec in &self.b {
            for item in sub_vec {
                result.extend(item);
            }
        }

        // Serialize 'c'
        for item in &self.c {
            result.extend(item);
        }

        result
    }

    /// Method to convert back from a `Vec<u8>`
    pub fn from_vec(data: &[u8]) -> Result<Seal, Error> {
        if data.len() != Self::SIZE {
            return Err(anyhow!("Data length mismatch"));
        }

        let mut offset = 0;
        let mut a = Vec::with_capacity(2);
        let mut b = Vec::with_capacity(2);
        let mut c = Vec::with_capacity(2);

        // Deserialize 'a'
        for _ in 0..2 {
            a.push(data[offset..offset + Self::ELEMENT_SIZE].to_vec());
            offset += Self::ELEMENT_SIZE;
        }

        // Deserialize 'b'
        for _ in 0..2 {
            let mut sub_vec = Vec::with_capacity(2);
            for _ in 0..2 {
                sub_vec.push(data[offset..offset + Self::ELEMENT_SIZE].to_vec());
                offset += Self::ELEMENT_SIZE;
            }
            b.push(sub_vec);
        }

        // Deserialize 'c'
        for _ in 0..2 {
            c.push(data[offset..offset + Self::ELEMENT_SIZE].to_vec());
            offset += Self::ELEMENT_SIZE;
        }

        Ok(Seal { a, b, c })
    }
}

impl TryFrom<ProofJson> for Seal {
    type Error = Error;
    fn try_from(proof: ProofJson) -> Result<Self, Error> {
        if proof.pi_a.len() < 2 {
            return Err(anyhow!("Malformed G1 element field"));
        }
        let a = vec![from_u256(&proof.pi_a[0])?, from_u256(&proof.pi_a[1])?];

        if proof.pi_b.len() < 2 || proof.pi_b[0].len() < 2 || proof.pi_b[1].len() < 2 {
            return Err(anyhow!("Malformed G2 element field"));
        }
        let b = vec![
            vec![from_u256(&proof.pi_b[0][1])?, from_u256(&proof.pi_b[0][0])?],
            vec![from_u256(&proof.pi_b[1][1])?, from_u256(&proof.pi_b[1][0])?],
        ];

        if proof.pi_c.len() < 2 {
            return Err(anyhow!("Malformed G1 element field"));
        }
        let c = vec![from_u256(&proof.pi_c[0])?, from_u256(&proof.pi_c[1])?];

        Ok(Seal { a, b, c })
    }
}

/// Groth16 Proof encoded as JSON.
#[derive(Serialize, Deserialize, Debug)]
pub struct ProofJson {
    pi_a: Vec<String>,
    pi_b: Vec<Vec<String>>,
    pi_c: Vec<String>,
    protocol: Option<String>,
    curve: Option<String>,
}

/// Groth16 Verifying Key encoded as JSON.
#[derive(Serialize, Deserialize, Debug)]
pub struct VerifyingKeyJson {
    protocol: String,
    curve: String,
    #[serde(rename = "nPublic")]
    n_public: u32,
    vk_alpha_1: Vec<String>,
    vk_beta_2: Vec<Vec<String>>,
    vk_gamma_2: Vec<Vec<String>>,
    vk_delta_2: Vec<Vec<String>>,
    vk_alphabeta_12: Vec<Vec<Vec<String>>>,
    #[serde(rename = "IC")]
    ic: Vec<Vec<String>>,
}

impl VerifyingKeyJson {
    /// Computes the prepared verifying key
    pub fn verifying_key(&self) -> Result<VerifyingKey, Error> {
        if self.vk_alpha_1.len() < 2 {
            return Err(anyhow!("Malformed G1 element field: vk_alpha_1"));
        }
        let alpha_g1 = g1_from_bytes(&[
            from_u256(&self.vk_alpha_1[0])?,
            from_u256(&self.vk_alpha_1[1])?,
        ])?;

        if self.vk_beta_2.len() < 2 || self.vk_beta_2[0].len() < 2 || self.vk_beta_2[1].len() < 2 {
            return Err(anyhow!("Malformed G2 element field: vk_beta_2"));
        }
        let beta_g2 = g2_from_bytes(&[
            vec![
                from_u256(&self.vk_beta_2[0][1])?,
                from_u256(&self.vk_beta_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_beta_2[1][1])?,
                from_u256(&self.vk_beta_2[1][0])?,
            ],
        ])?;

        if self.vk_gamma_2.len() < 2 || self.vk_gamma_2[0].len() < 2 || self.vk_gamma_2[1].len() < 2
        {
            return Err(anyhow!("Malformed G2 element field: vk_gamma_2"));
        }
        let gamma_g2 = g2_from_bytes(&[
            vec![
                from_u256(&self.vk_gamma_2[0][1])?,
                from_u256(&self.vk_gamma_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_gamma_2[1][1])?,
                from_u256(&self.vk_gamma_2[1][0])?,
            ],
        ])?;

        if self.vk_delta_2.len() < 2 || self.vk_delta_2[0].len() < 2 || self.vk_delta_2[1].len() < 2
        {
            return Err(anyhow!("Malformed G2 element field: vk_delta_2"));
        }
        let delta_g2 = g2_from_bytes(&[
            vec![
                from_u256(&self.vk_delta_2[0][1])?,
                from_u256(&self.vk_delta_2[0][0])?,
            ],
            vec![
                from_u256(&self.vk_delta_2[1][1])?,
                from_u256(&self.vk_delta_2[1][0])?,
            ],
        ])?;

        let gamma_abc_g1 = self
            .ic
            .iter()
            .enumerate()
            .map(|(i, ic)| {
                if ic.len() < 2 {
                    return Err(anyhow!("Malformed G1 element field: IC_{i}"));
                }
                g1_from_bytes(&[from_u256(&ic[0])?, from_u256(&ic[1])?])
            })
            .collect::<Result<Vec<_>, _>>()?;

        Ok(VerifyingKey(Vk {
            alpha_g1,
            beta_g2,
            gamma_g2,
            delta_g2,
            gamma_abc_g1,
        }))
    }
}

/// A groth16 verification key (TODO)
/// 
/// A verification key. It needs to be prepared into a [Pvk] before use. (TODO)
// TODO: Derives?
#[derive(Clone, Debug, Eq, PartialEq)]
pub struct Vk {
    // TODO: better pattern for access?
    pub(crate) alpha_g1: substrate_bn::G1,
    pub(crate) beta_g2: substrate_bn::G2,
    pub(crate) gamma_g2: substrate_bn::G2,
    pub(crate) delta_g2: substrate_bn::G2,
    pub(crate) gamma_abc_g1: Vec<substrate_bn::G1>,
}

impl Serialize for Vk {
    fn serialize<S>(&self, serializer: S) -> core::result::Result<S::Ok, S::Error>
    where
        S: serde::Serializer
    {
        let mut state = serializer.serialize_struct("Vk", 5)?;
        state.serialize_field("alpha_g1", &G1data::from(self.alpha_g1))?;
        state.serialize_field("beta_g2", &G2data::from(self.beta_g2))?;
        state.serialize_field("gamma_g2", &G2data::from(self.gamma_g2))?;
        state.serialize_field("delta_g2", &G2data::from(self.delta_g2))?;
        // TODO: This clone can probably be avoided
        state.serialize_field("gamma_abc_g1", &G1dataVec::from(self.gamma_abc_g1.clone()))?;
        state.end()
    }
}

impl<'de> Deserialize<'de> for Vk {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>
    {
        enum Field {
            AlphaG1,
            BetaG2,
            GammaG2,
            DeltaG2,
            GammaABCG1,
        }

        impl<'de> Deserialize<'de> for Field {
            fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
            where
                D: serde::Deserializer<'de>
            {
                struct FieldVisitor;

                impl<'de> serde::de::Visitor<'de> for FieldVisitor {
                    type Value = Field;

                    fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                        formatter.write_str("`alpha_g1`, `beta_g2`, `gamma_g2`, `delta_g2`, or `gamma_abc_g1`")
                    }

                    fn visit_str<E>(self, value: &str) -> Result<Self::Value, E>
                    where
                        E: serde::de::Error,
                    {
                        match value {
                            "alpha_g1" => Ok(Field::AlphaG1),
                            "beta_g2" => Ok(Field::BetaG2),
                            "gamma_g2" => Ok(Field::GammaG2),
                            "delta_g2" => Ok(Field::DeltaG2),
                            "gamma_abc_g1" => Ok(Field::GammaABCG1),
                            _ => Err(serde::de::Error::unknown_field(value, FIELDS))
                        }
                    }
                }

                deserializer.deserialize_identifier(FieldVisitor)
            }
        }

        struct VkVisitor;

        impl<'de> serde::de::Visitor<'de> for VkVisitor {
            type Value = Vk;

            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                // TODO: might be nicer message?
                formatter.write_str("struct Vk")
            }

            // TODO: Add testing for visit_seq (JSON serialization uses the map path instead)
            fn visit_seq<A>(self, mut seq: A) -> Result<Self::Value, A::Error>
            where
                A: serde::de::SeqAccess<'de>,
            {
                let alpha_g1: G1data = seq.next_element()?
                    .ok_or_else(|| serde::de::Error::invalid_length(0, &self))?;
                let beta_g2: G2data = seq.next_element()?
                    .ok_or_else(|| serde::de::Error::invalid_length(1, &self))?;
                let gamma_g2: G2data = seq.next_element()?
                    .ok_or_else(|| serde::de::Error::invalid_length(2, &self))?;
                let delta_g2: G2data = seq.next_element()?
                    .ok_or_else(|| serde::de::Error::invalid_length(3, &self))?;
                let gamma_abc_g1: G1dataVec = seq.next_element()?
                    .ok_or_else(|| serde::de::Error::invalid_length(4, &self))?;
                Ok(Vk {
                    alpha_g1: alpha_g1.into(),
                    beta_g2: beta_g2.into(),
                    gamma_g2: gamma_g2.into(),
                    delta_g2: delta_g2.into(),
                    gamma_abc_g1: gamma_abc_g1.into(),
                })
            }

            fn visit_map<V>(self, mut map: V) -> Result<Self::Value, V::Error>
            where
                V: serde::de::MapAccess<'de>,
            {
                let mut alpha_g1: Option<G1data> = None;
                let mut beta_g2: Option<G2data> = None;
                let mut gamma_g2: Option<G2data> = None;
                let mut delta_g2: Option<G2data> = None;
                let mut gamma_abc_g1: Option<G1dataVec> = None;
                while let Some(key) = map.next_key()? {
                    match key {
                        Field::AlphaG1 => {
                            if alpha_g1.is_some() {
                                return Err(serde::de::Error::duplicate_field("alpha_g1"));
                            }
                            alpha_g1 = Some(map.next_value()?);
                        }
                        Field::BetaG2 => {
                            if beta_g2.is_some() {
                                return Err(serde::de::Error::duplicate_field("beta_g2"));
                            }
                            beta_g2 = Some(map.next_value()?);
                        }
                        Field::GammaG2 => {
                            if gamma_g2.is_some() {
                                return Err(serde::de::Error::duplicate_field("gamma_g2"));
                            }
                            gamma_g2 = Some(map.next_value()?);
                        }
                        Field::DeltaG2 => {
                            if delta_g2.is_some() {
                                return Err(serde::de::Error::duplicate_field("delta_g2"));
                            }
                            delta_g2 = Some(map.next_value()?);
                        }
                        Field::GammaABCG1 => {
                            if gamma_abc_g1.is_some() {
                                return Err(serde::de::Error::duplicate_field("gamma_abc_g1"));
                            }
                            gamma_abc_g1 = Some(map.next_value()?);
                        }
                    }
                }
                let alpha_g1 = alpha_g1.ok_or_else(|| serde::de::Error::missing_field("alpha_g1"))?;
                let beta_g2 = beta_g2.ok_or_else(|| serde::de::Error::missing_field("beta_g2"))?;
                let gamma_g2 = gamma_g2.ok_or_else(|| serde::de::Error::missing_field("gamma_g2"))?;
                let delta_g2 = delta_g2.ok_or_else(|| serde::de::Error::missing_field("delta_g2"))?;
                let gamma_abc_g1 = gamma_abc_g1.ok_or_else(|| serde::de::Error::missing_field("gamma_abc_g1"))?;
                Ok(Vk {
                    alpha_g1: alpha_g1.into(),
                    beta_g2: beta_g2.into(),
                    gamma_g2: gamma_g2.into(),
                    delta_g2: delta_g2.into(),
                    gamma_abc_g1: gamma_abc_g1.into(),
                })
            }
        }
        const FIELDS: &[&str] = &["alpha_g1", "beta_g2", "gamma_g2", "delta_g2", "gamma_abc_g1"];
        deserializer.deserialize_struct("Vk", FIELDS, VkVisitor)
    }
}

// TODO: Helper struct for Vk serialization
// TODO: I don't think this is as efficient of a design as it could be
#[derive(Serialize, Deserialize)]
struct G1dataVec(Vec<G1data>);

impl From<Vec<substrate_bn::G1>> for G1dataVec {
    fn from(item: Vec<substrate_bn::G1>) -> Self {
        let mut res = G1dataVec(Vec::<G1data>::new());
        for val in item {
            res.0.push(val.into());
        }
        res
    }
}

impl From<G1dataVec> for Vec<substrate_bn::G1> {
    fn from(item: G1dataVec) -> Self {
        let mut res = Vec::<substrate_bn::G1>::new();
        for val in item.0 {
            res.push(val.into());
        }
        res
    }
}

// TODO: Helper struct for Vk serialization
struct G1data([u8; 96]);

impl From<substrate_bn::G1> for G1data {
    fn from(item: substrate_bn::G1) -> Self {
        // TODO: We could save space with a compressed representation
        let mut buf = [0u8; 96];
        item.x().to_big_endian(&mut buf[0..32]).expect("output buffer is 32 bytes");
        item.y().to_big_endian(&mut buf[32..64]).expect("output buffer is 32 bytes");
        item.z().to_big_endian(&mut buf[64..96]).expect("output buffer is 32 bytes");
        G1data(buf)
    }
}

// TODO: Swap to TryFrom instead of using unwrap
impl From<G1data> for substrate_bn::G1 {
    fn from(item: G1data) -> Self {
        substrate_bn::G1::new(
            substrate_bn::Fq::from_slice(&item.0[0..32]).unwrap(),
            substrate_bn::Fq::from_slice(&item.0[32..64]).unwrap(),
            substrate_bn::Fq::from_slice(&item.0[64..96]).unwrap(),
        )
    }
}

impl Serialize for G1data {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        // serializer.serialize_bytes(&self.0)  // TODO: can only use if `visit_bytes` works
        // TODO: Deprecate below code and replace with above once `serde_bytes` works
        let mut seq = serializer.serialize_seq(Some(96))?;
        for val in self.0 {
            seq.serialize_element(&val)?;
        }
        seq.end()
    }
}

impl<'de> Deserialize<'de> for G1data {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        struct G1dataVisitor;

        impl<'de> serde::de::Visitor<'de> for G1dataVisitor {
            type Value = G1data;

            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                // TODO: might be nicer message?
                formatter.write_str("struct G1data")
            }

            fn visit_bytes<E>(self, v: &[u8]) -> Result<Self::Value, E>
            where
                E: serde::de::Error,
            {
                // TODO: This doesn't get called, and I'm not clear how to use serde_bytes in this context to address that
                Ok(G1data(v
                    .try_into()
                    .map_err (|_|serde::de::Error::invalid_length(v.len(), &"96 bytes"))?
                ))
            }

            fn visit_seq<V>(self, mut seq: V) -> Result<Self::Value, V::Error>
            where
                V: serde::de::SeqAccess<'de>,
            {
                // TODO: I would rather use `visit_bytes`, but that requires figuring out the `serde_bytes` crate
                let mut pos = 0usize;
                let mut data = G1data([0u8; 96]);
                for val in data.0.iter_mut() {
                    *val = seq.next_element()?.ok_or_else(|| serde::de::Error::invalid_length(pos, &"96 bytes"))?;
                    pos += 1;
                }
                match seq.next_element::<u8>()?.is_none() {
                    true => Ok(data),
                    // TODO: Cleaner error
                    false => Err(serde::de::Error::invalid_length(97, &"96 bytes (note: all lengths above 96 bytes are reported as 97 bytes)")),
                }
            }
        }
        // TODO: Uh, shouldn't this be deserialize_seq?
        deserializer.deserialize_bytes(G1dataVisitor)
    }
}


// TODO: Helper struct for Vk serialization
struct G2data([u8; 192]);

impl From<substrate_bn::G2> for G2data {
    fn from(item: substrate_bn::G2) -> Self {
        // TODO: We could save space with a compressed representation
        let mut buf = [0u8; 192];
        item.x().real().to_big_endian(&mut buf[0..32]).expect("output buffer is 32 bytes");
        item.x().imaginary().to_big_endian(&mut buf[32..64]).expect("output buffer is 32 bytes");
        item.y().real().to_big_endian(&mut buf[64..96]).expect("output buffer is 32 bytes");
        item.y().imaginary().to_big_endian(&mut buf[96..128]).expect("output buffer is 32 bytes");
        item.z().real().to_big_endian(&mut buf[128..160]).expect("output buffer is 32 bytes");
        item.z().imaginary().to_big_endian(&mut buf[160..192]).expect("output buffer is 32 bytes");
        G2data(buf)
    }
}

// TODO: Swap to TryFrom instead of using unwrap
impl From<G2data> for substrate_bn::G2 {
    fn from(item: G2data) -> Self {
        substrate_bn::G2::new(
            substrate_bn::Fq2::new(
                substrate_bn::Fq::from_slice(&item.0[0..32]).unwrap(),
                substrate_bn::Fq::from_slice(&item.0[32..64]).unwrap(),
            ),
            substrate_bn::Fq2::new(
                substrate_bn::Fq::from_slice(&item.0[64..96]).unwrap(),
                substrate_bn::Fq::from_slice(&item.0[96..128]).unwrap(),
            ),
            substrate_bn::Fq2::new(
                substrate_bn::Fq::from_slice(&item.0[128..160]).unwrap(),
                substrate_bn::Fq::from_slice(&item.0[160..192]).unwrap(),
            ),
        )
    }
}

impl Serialize for G2data {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        // serializer.serialize_bytes(&self.0)  // TODO: can only use if `visit_bytes` works
        // TODO: Deprecate below code and replace with above once `serde_bytes` works
        let mut seq = serializer.serialize_seq(Some(192))?;
        for val in self.0 {
            seq.serialize_element(&val)?;
        }
        seq.end()
    }
}

impl<'de> Deserialize<'de> for G2data {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        struct G2dataVisitor;

        impl<'de> serde::de::Visitor<'de> for G2dataVisitor {
            type Value = G2data;

            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                // TODO: might be nicer message?
                formatter.write_str("struct G2data")
            }

            fn visit_bytes<E>(self, v: &[u8]) -> Result<Self::Value, E>
            where
                E: serde::de::Error,
            {
                // TODO: This doesn't get called, and I'm not clear how to use serde_bytes in this context to address that
                Ok(G2data(v
                    .try_into()
                    .map_err (|_|serde::de::Error::invalid_length(v.len(), &"192 bytes"))?
                ))
            }

            fn visit_seq<V>(self, mut seq: V) -> Result<Self::Value, V::Error>
            where
                V: serde::de::SeqAccess<'de>,
            {
                // TODO: I would rather use `visit_bytes`, but that requires figuring out the `serde_bytes` crate
                let mut pos = 0usize;
                let mut data = G2data([0u8; 192]);
                for val in data.0.iter_mut() {
                    *val = seq.next_element()?.ok_or_else(|| serde::de::Error::invalid_length(pos, &"192 bytes"))?;
                    pos += 1;
                }
                match seq.next_element::<u8>()?.is_none() {
                    true => Ok(data),
                    // TODO: Cleaner error
                    false => Err(serde::de::Error::invalid_length(193, &"192 bytes (note: all lengths above 192 bytes are reported as 193 bytes)")),
                }
            }
        }
        // TODO: Shouldn't this be deserialize_seq?
        deserializer.deserialize_bytes(G2dataVisitor)
    }
}

/// Verifying key for Groth16 proofs.
// TODO: Want full traits
// #[derive(Clone, Debug, Serialize, Deserialize)]
#[derive(Clone, Debug)]
pub struct Fr(pub(crate) substrate_bn::Fr);

impl Fr {
    #[stability::unstable]
    pub fn substrate_fr(&self) -> substrate_bn::Fr {
        self.0
    }
}

impl Serialize for Fr {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: serde::Serializer,
    {
        let mut bytes = [0u8; 32];
        // Note: Must do `into_u256().to_big_endian()` and not just `.to_big_endian()` because the
        // latter writes in Montgomery form, and both `from_slice` and `new` expect canonical form
        self.0.into_u256().to_big_endian(&mut bytes).expect("Only fails if output buffer isn't 32 bytes");
        // serializer.serialize_bytes(&bytes)  // TODO: can only use if `visit_bytes` works
        // TODO: Deprecate below code and replace with above once `serde_bytes` works
        let mut seq = serializer.serialize_seq(Some(32))?;
        for val in bytes {
            seq.serialize_element(&val)?;
        }
        seq.end()
    }
}

impl<'de> Deserialize<'de> for Fr {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        struct FrVisitor;

        impl<'de> serde::de::Visitor<'de> for FrVisitor {
            type Value = Fr;

            fn expecting(&self, formatter: &mut fmt::Formatter) -> fmt::Result {
                // TODO: might be nicer message?
                formatter.write_str("struct Fr")
            }

            fn visit_seq<V>(self, mut seq: V) -> Result<Self::Value, V::Error>
            where
                V: serde::de::SeqAccess<'de>,
            {
                // TODO: I would rather use `visit_bytes`, but that requires figuring out the `serde_bytes` crate
                let mut pos = 0usize;
                let mut data = [0u8; 32];
                for val in data.iter_mut() {
                    *val = seq.next_element()?.ok_or_else(|| serde::de::Error::invalid_length(pos, &"32 bytes"))?;
                    pos += 1;
                }
                match seq.next_element::<u8>()?.is_none() {
                    true => Ok(Fr(substrate_bn::Fr::from_slice(&data).expect("Only fails if input buffer isn't 32 bytes"))),
                    // TODO: Cleaner error
                    false => Err(serde::de::Error::invalid_length(33, &"32 bytes (note: all lengths above 32 bytes are reported as 33 bytes)")),
                }
            }
        }
        deserializer.deserialize_seq(FrVisitor)
    }
}

// TODO: Add a test for this?
impl Digestible for Fr {
    /// Compute a tagged hash of the [Fr] value.
    fn digest<S: Sha256>(&self) -> Digest {
        // TODO: Why not an array?
        let mut buffer = Vec::<u8>::with_capacity(32);
        // Serialization into a pre-allocated buffer should never fail.
        self.0.into_u256().to_big_endian(&mut buffer).unwrap();
        // TODO: Do we need the exact same digests as before? If so, figure out further what if any changes are needed
        tagged_struct::<S>(
            "risc0_groth16.Fr",
            &[bytemuck::pod_read_unaligned::<Digest>(&buffer)],
            &[],
        )
    }
}

/// A prepared groth16 verification key (TODO)
/// 
/// TODO: Note that status quo this doesn't contain the original verification key and so can't be regenerated
#[derive(Clone)]
pub struct Pvk {
    // TODO: better pattern for access?
    pub(crate) vk: Vk,
    pub(crate) alpha_g1_beta_g2: substrate_bn::Gt,
    pub(crate) gamma_g2_neg_pc: substrate_bn::G2,
    pub(crate) delta_g2_neg_pc: substrate_bn::G2,
}

// TODO: Or is it TryFrom?
impl From<Vk> for Pvk {
    fn from(item: Vk) -> Self {
        Pvk {
            vk: item.clone(),  // TODO: Hmm do I really need to clone?
            alpha_g1_beta_g2: substrate_bn::pairing(item.alpha_g1.into(), item.beta_g2.into()),  // Note: `pairing` includes final exponentiation
            gamma_g2_neg_pc: -item.gamma_g2,
            delta_g2_neg_pc: -item.delta_g2,
        }
    }
}

/// Groth16 Public witness encoded as JSON.
#[derive(Serialize, Deserialize, Debug)]
pub struct PublicInputsJson {
    /// values of the public witness
    pub values: Vec<String>,
}

impl PublicInputsJson {
    /// Converts public inputs to scalars over the field of the G1/G2 groups.
    pub fn to_scalar(&self) -> Result<Vec<crate::Fr>, Error> {
        self.values
            .iter()
            .map(|input| {
                substrate_bn::Fr::from_str(input)
                    .ok_or_else(||anyhow!("Failed to decode 'public inputs' values"))
                    .map(crate::Fr)
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    // TODO
    use substrate_bn::Group;

    #[test]
    fn test_proof_deserialization() {
        let json_data = r#"
        {
            "pi_a": [
            "19752044163435112998099796779947263139365269296294968520404327719124263547111",
            "11069769267857023583069178672374572453291648685282843843698422556496935187114",
            "1"
            ],
            "pi_b": [
            [
            "10648747807246846520146780919185052825636963110330658206295040747407885055071",
            "12804372218404923567755746304221068640275041956837635530943827697901769703079"
            ],
            [
            "2503338810872511988681832059415719063350505376876347903054293313634087665155",
            "9633905142041006786673594506047895273339766343254274246797495142581149020665"
            ],
            [
            "1",
            "0"
            ]
            ],
            "pi_c": [
            "3377589055768505200338103068502385766692581078477457038865468586522780813958",
            "3539307538774736362004944548122522044958136460057956047632676706584864343097",
            "1"
            ]
        }
    "#;

        let _proof: ProofJson =
            serde_json::from_str(json_data).expect("JSON was not well-formatted");
    }

    #[test]
    fn test_vkey_deserialization() {
        let json_data = r#"
        {
            "protocol": "groth16",
            "curve": "bn128",
            "nPublic": 1,
            "vk_alpha_1": [
            "1294134766316609703328581643861691998063901679593305122518960283123018706388",
            "13333629383043588737044454681202570079155905422740155054898346012606076806713",
            "1"
            ],
            "vk_beta_2": [
            [
            "2173330313723596358484167553880140545051512882245565043987444676076276437843",
            "17664927106745560489997587182635122110932281433243608150300401610335045630458"
            ],
            [
            "15273531101849588270786039343703563036519656806292651941045419058100734479928",
            "5906890440295795612829674167362972238653435457353882556276325798552943068201"
            ],
            [
            "1",
            "0"
            ]
            ],
            "vk_gamma_2": [
            [
            "10857046999023057135944570762232829481370756359578518086990519993285655852781",
            "11559732032986387107991004021392285783925812861821192530917403151452391805634"
            ],
            [
            "8495653923123431417604973247489272438418190587263600148770280649306958101930",
            "4082367875863433681332203403145435568316851327593401208105741076214120093531"
            ],
            [
            "1",
            "0"
            ]
            ],
            "vk_delta_2": [
            [
            "18082335820320067675049162254051449653127391848352997939790860074257698080107",
            "8330577861444131504217321247245855407953761241369242366142989304032525780907"
            ],
            [
            "17303423980605275724415088817235493141378511193276153617545225405070114888674",
            "14329686539600445325529176452626235089284148901536698629845437848687632586506"
            ],
            [
            "1",
            "0"
            ]
            ],
            "vk_alphabeta_12": [
            [
            [
                "21597631232807937363539811467397773006510227572521934676321553463646334198635",
                "262163796566031525966924304077669698911462791938684055481358366761190909624"
            ],
            [
                "7906541510069809568866569458625474906165138266731006158097677153173003081190",
                "6033731974653073317939840745456215697935806048520129111479696325287019924880"
            ],
            [
                "14704987171684462743284913958358496425592435250893903733996815280116183837956",
                "11976893335360452767634479785443059483596766884568778627130863225715341853664"
            ]
            ],
            [
            [
                "12328097080442051249349425344337187894102839822992588206855395089786926203816",
                "13682208775939290403599679510439179899909912951037259533145887567028127550386"
            ],
            [
                "21192833402016971123221885086549612170051010389337807472438934720324822965947",
                "13562414185694763175024854871060329561479364355902009699411281367056182859582"
            ],
            [
                "19521540372565909644039072005218101866465290490181239648233003077758316514534",
                "14972591569740303137698557285367668726475164123365050189180689552096060582998"
            ]
            ]
            ],
            "IC": [
            [
            "14881188593619314262120916669096182039078823054228847940501571078734139590733",
            "14154402986581165757157012590900333439821186463176177723513413360706693112432",
            "1"
            ],
            [
            "12590475535581033066201434982368662557531886044597804777316719198629101964198",
            "15378991198052714418783412681738830395150582056324300616272352953924768221974",
            "1"
            ]
            ]
        }
        "#;

        let vk: VerifyingKeyJson =
            serde_json::from_str(json_data).expect("JSON was not well-formatted");
        assert_eq!(vk.protocol, "groth16");
        assert_eq!(vk.curve, "bn128");
        assert_eq!(vk.n_public, 1);
        let vk = vk.verifying_key().unwrap();

        // Now test serde roundtrip
        let serialized = serde_json::to_string(&vk).unwrap();
        let roundtripped_vk: VerifyingKey = serde_json::from_str(&serialized).unwrap();
        assert_eq!(roundtripped_vk, vk);

        // Verifying that a manipulated version doesn't match the roundtrip
        let mut vk_manipulated = vk.clone();
        vk_manipulated.0.beta_g2 = vk_manipulated.0.beta_g2 + substrate_bn::G2::one();
        assert_ne!(roundtripped_vk, vk_manipulated);
    }

    #[test]
    fn test_g1_serde_roundtrip() {
        let val = substrate_bn::G1::one();
        let serialized = serde_json::to_string(&G1data::from(val)).unwrap();
        let deserialized: G1data = serde_json::from_str(&serialized).unwrap();
        let roundtripped_val: substrate_bn::G1 = deserialized.into();
        assert_eq!(roundtripped_val, val);
    }

    #[test]
    fn test_g2_serde_roundtrip() {
        let val = substrate_bn::G2::one();
        let serialized = serde_json::to_string(&G2data::from(val)).unwrap();
        let deserialized: G2data = serde_json::from_str(&serialized).unwrap();
        let roundtripped_val: substrate_bn::G2 = deserialized.into();
        assert_eq!(roundtripped_val, val);
    }

    #[test]
    fn test_vk_serde_roundtrip() {
        let val = substrate_bn::G2::one();
        let serialized = serde_json::to_string(&G2data::from(val)).unwrap();
        let deserialized: G2data = serde_json::from_str(&serialized).unwrap();
        let roundtripped_val: substrate_bn::G2 = deserialized.into();
        assert_eq!(roundtripped_val, val);
    }

    #[test]
    fn test_fr_serde_roundtrip() {
        let val = substrate_bn::Fr::one();
        let serialized = serde_json::to_string(&Fr(val)).unwrap();
        let deserialized: Fr = serde_json::from_str(&serialized).unwrap();
        let roundtripped_val: substrate_bn::Fr = deserialized.0;
        assert_eq!(roundtripped_val, val);
    }
}
