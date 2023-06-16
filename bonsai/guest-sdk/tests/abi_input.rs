// Copyright 2023 RISC Zero, Inc.
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

use bonsai_guest_sdk::EthABIReader;
use ethabi::{ethereum_types::U256, ParamType, Token};

#[test]
pub fn test_abi_input_construction() {
    let vec_input = Box::new(vec![0u8; 32]);
    EthABIReader::new(vec_input);

    let env_input = Box::new(());
    EthABIReader::new(env_input);
}

#[test]
pub fn test_abi_input_simple() {
    let tokens = [
        Token::Uint(U256::from(1u128 << 120)),
        Token::Uint(U256::from(1u128 << 120)),
    ];

    let types = [ParamType::Uint(256), ParamType::Uint(256)];
    // assert success
    assert!(check_read_length(&tokens, &types));
}

#[test]
pub fn test_abi_input_fixed_array() {
    let tokens = [Token::FixedArray(vec![
        Token::Uint(U256::from(1u128 << 120)),
        Token::Uint(U256::from(1u128 << 120)),
        Token::Uint(U256::from(1u128 << 120)),
    ])];

    let types = [ParamType::FixedArray(Box::from(ParamType::Uint(256)), 2)];
    // assert failure
    assert!(!check_read_length(&tokens, &types));
    let types = [ParamType::FixedArray(Box::from(ParamType::Uint(256)), 3)];
    // assert success
    assert!(check_read_length(&tokens, &types));
}

#[test]
pub fn test_abi_input_dynamic_array() {
    let tokens = [Token::Array(vec![
        Token::Uint(U256::from(1u128 << 120)),
        Token::Uint(U256::from(1u128 << 120)),
        Token::Uint(U256::from(1u128 << 120)),
    ])];

    let types = [ParamType::Array(Box::from(ParamType::Uint(256)))];
    // assert success
    assert!(check_read_length(&tokens, &types));
}

#[test]
pub fn test_abi_input_tuple_dynamic() {
    let tokens = [Token::Tuple(vec![
        Token::Uint(U256::from(1u128 << 120)),
        Token::Array(vec![
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
        ]),
        Token::Uint(U256::from(1u128 << 120)),
        Token::FixedArray(vec![
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
        ]),
    ])];

    let types = [ParamType::Tuple(vec![
        ParamType::Uint(256),
        ParamType::Array(Box::from(ParamType::Uint(256))),
        ParamType::Uint(256),
        ParamType::FixedArray(Box::new(ParamType::Uint(256)), 3),
    ])];
    // assert success
    assert!(check_read_length(&tokens, &types));
}

#[test]
pub fn test_abi_input_tuple_fixed() {
    let bytes = "abracadarba".as_bytes().to_vec();
    let byte_len = bytes.len();
    let tokens = [Token::Tuple(vec![
        Token::FixedArray(vec![Token::Uint(U256::from(1u128 << 120))]),
        Token::Uint(U256::from(1u128 << 120)),
        Token::FixedArray(vec![
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
        ]),
        Token::Uint(U256::from(1u128 << 120)),
        Token::FixedArray(vec![
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
        ]),
        Token::FixedBytes(bytes),
    ])];

    let types = [ParamType::Tuple(vec![
        ParamType::FixedArray(Box::new(ParamType::Uint(256)), 1),
        ParamType::Uint(256),
        ParamType::FixedArray(Box::new(ParamType::Uint(256)), 3),
        ParamType::Uint(256),
        ParamType::FixedArray(Box::new(ParamType::Uint(256)), 5),
        ParamType::FixedBytes(byte_len),
    ])];
    // assert success
    assert!(check_read_length(&tokens, &types));
}
#[test]
pub fn test_abi_input_tuple_nested() {
    let bytes = "abracadarba".as_bytes().to_vec();
    let byte_len = bytes.len();
    let tokens = [Token::Tuple(vec![
        Token::FixedArray(vec![Token::Uint(U256::from(1u128 << 120))]),
        Token::Uint(U256::from(1u128 << 120)),
        Token::FixedArray(vec![
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
        ]),
        Token::Uint(U256::from(1u128 << 120)),
        Token::Tuple(vec![
            Token::Uint(U256::from(1u128 << 120)),
            Token::Array(vec![
                Token::Uint(U256::from(1u128 << 120)),
                Token::Uint(U256::from(1u128 << 120)),
                Token::Uint(U256::from(1u128 << 120)),
                Token::Uint(U256::from(1u128 << 120)),
                Token::Uint(U256::from(1u128 << 120)),
            ]),
            Token::Uint(U256::from(1u128 << 120)),
            Token::FixedArray(vec![
                Token::Uint(U256::from(1u128 << 120)),
                Token::Uint(U256::from(1u128 << 120)),
                Token::Uint(U256::from(1u128 << 120)),
            ]),
        ]),
        Token::FixedArray(vec![
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
            Token::Uint(U256::from(1u128 << 120)),
        ]),
        Token::FixedBytes(bytes),
    ])];

    let types = [ParamType::Tuple(vec![
        ParamType::FixedArray(Box::new(ParamType::Uint(256)), 1),
        ParamType::Uint(256),
        ParamType::FixedArray(Box::new(ParamType::Uint(256)), 3),
        ParamType::Uint(256),
        ParamType::Tuple(vec![
            ParamType::Uint(256),
            ParamType::Array(Box::from(ParamType::Uint(256))),
            ParamType::Uint(256),
            ParamType::FixedArray(Box::new(ParamType::Uint(256)), 3),
        ]),
        ParamType::FixedArray(Box::new(ParamType::Uint(256)), 5),
        ParamType::FixedBytes(byte_len),
    ])];
    // assert success
    assert!(check_read_length(&tokens, &types));
}

fn check_read_length(tokens: &[Token], types: &[ParamType]) -> bool {
    let vec_input = ethabi::encode(tokens);
    dbg!(hex::encode(&vec_input));
    let byte_length = vec_input.len();
    let mut reader = EthABIReader::new(Box::new(vec_input));
    let mut buffer = Vec::new();
    reader.read_abi_encoded_input(types, &mut buffer, 0, 0);
    let buffered_length = buffer.len();
    dbg!(&byte_length);
    dbg!(&buffered_length);
    let result = byte_length == buffered_length;
    if result {
        // validate success scenarios
        assert_eq!(ethabi::decode(types, &buffer).unwrap().as_slice(), tokens);
    }
    result
}
