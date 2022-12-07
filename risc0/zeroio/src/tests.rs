// Copyright 2022 RISC Zero, Inc.
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

use alloc::{boxed::Box, string::String, vec::Vec};
use core::fmt::Debug;

use test_log::test;

use super::{serialize, Deserialize, DeserializeOwned, Serialize, PAD_WORDS};
use crate as risc0_zeroio;

#[derive(Serialize, Deserialize, PartialEq, Eq, Debug, Clone)]
struct StructContainer<T: Eq + Serialize + Debug + DeserializeOwned> {
    a: u32,
    b: T,
    c: u32,
}

#[derive(Serialize, Deserialize, Debug, PartialEq, Eq, Clone)]
struct StructContainer2<T: Debug + Serialize + Eq + Clone + DeserializeOwned> {
    a: u32,
    b: (u32, Option<T>),
    c: u32,
}

#[derive(Serialize, Deserialize, Debug, PartialEq, Eq, Clone)]
struct StructContainer3<T: Debug + Serialize + Eq + Clone + DeserializeOwned> {
    a: u32,
    b: Box<StructContainer2<T>>,
    c: u32,
}

pub fn test_round_trip_no_containers<T: Serialize + DeserializeOwned + Eq + Debug + Clone>(
    val: &T,
) {
    let u32s: Vec<u32> = serialize(val).unwrap();
    assert_eq!(u32s.len() % PAD_WORDS, 0);

    let deser = T::deserialize_from(&u32s);
    let actual = T::from_ref(&deser);

    assert_eq!(*val, actual);
}

pub fn test_round_trip<T: Serialize + DeserializeOwned + Eq + Debug + Clone>(val: &T) {
    test_round_trip_no_containers(val);

    test_round_trip_no_containers(&StructContainer::<T> {
        a: 1,
        b: val.clone(),
        c: 2,
    });

    test_round_trip_no_containers(&Vec::<StructContainer2<T>>::from([
        StructContainer2::<T> {
            a: 3,
            b: (20, None),
            c: 4,
        },
        StructContainer2::<T> {
            a: 5,
            b: (21, Some(val.clone())),
            c: 6,
        },
    ]));

    test_round_trip_no_containers(&Vec::<Option<StructContainer3<T>>>::from([
        Some(StructContainer3::<T> {
            a: 7,
            b: Box::from(StructContainer2::<T> {
                a: 8,
                b: (22, Some(val.clone())),
                c: 9,
            }),
            c: 10,
        }),
        None,
    ]));
}

#[test]
fn basic_types() {
    test_round_trip(&0u32);
    test_round_trip(&1u32);
    test_round_trip(&u32::MAX);
    test_round_trip(&String::from(""));
    test_round_trip(&String::from("How"));
    test_round_trip(&String::from("Howd"));
    test_round_trip(&String::from("Howdy"));
    test_round_trip(&[1u32, 2, 3]);
    test_round_trip(&[1u32, 2, 3, 4]);
    test_round_trip(&[1u32, 2, 3, 4, 5]);
    test_round_trip(&());
}

#[derive(Serialize, Deserialize, PartialEq, Eq, Debug, Clone)]
struct SimpleStruct {
    a: u32,
}

#[derive(Serialize, Deserialize, PartialEq, Eq, Debug, Clone)]
enum MultiEnum {
    Val1,
    Val2(StructContainer3<MultiEnum>),
    Val3,
}

#[test]
fn structs_enums() {
    test_round_trip(&SimpleStruct { a: 3 });
    test_round_trip(&MultiEnum::Val1);
    test_round_trip(&MultiEnum::Val2(StructContainer3 {
        a: 7,
        b: Box::from(StructContainer2 {
            a: 8,
            b: (22, Some(MultiEnum::Val1)),
            c: 9,
        }),
        c: 10,
    }));
    test_round_trip(&MultiEnum::Val3);

    let u8s: Vec<u8> = Vec::from([1, 2, 3, 4, 5].as_slice());
    test_round_trip(&u8s);
}

#[derive(Serialize, Deserialize, PartialEq, Eq, Debug, Clone)]
struct Arrays {
    a: [u8; 7],
    b: [u8; 16],
}

#[test]
fn arrays() {
    test_round_trip(&Arrays {
        a: [1, 2, 3, 4, 5, 6, 7],
        b: [
            11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
        ],
    });
}
