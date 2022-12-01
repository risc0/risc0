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

use alloc::boxed::Box;

use risc0_zeroio_derive::{Deserialize, Serialize};
use test_log::test;

use super::*;
use crate as risc0_zeroio;

#[derive(Debug, Serialize, Deserialize, PartialEq, Eq)]
struct MyStruct {
    foo: u32,
    bar: alloc::string::String,
    next: Option<Box<MyStruct>>,
}

#[test]
pub fn ser_test() {
    let a = MyStruct {
        foo: 5,
        bar: "hi".into(),
        next: None,
    };

    let b = serialize(&a).unwrap();
    let des = MyStruct::deserialize_from(&*b);
    let mys: MyStruct = MyStruct::from_ref(&des);
    assert_eq!(a, mys);
}

#[test]
pub fn ser_test_link() {
    let a = MyStruct {
        foo: 5,
        bar: "hi".into(),
        next: Some(Box::new(MyStruct {
            foo: 6,
            bar: "Why hello there!".into(),
            next: None,
        })),
    };

    let b = serialize(&a).unwrap();
    let des = MyStruct::deserialize_from(&*b);
    let mys: MyStruct = MyStruct::from_ref(&des);
    assert_eq!(a, mys);
}
