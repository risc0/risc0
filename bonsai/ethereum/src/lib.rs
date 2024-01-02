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

//! Specifies the Bonsai Relay Ethereum contract and provides
//! structures and procedures for programmatic deployment of and interaction
//! with a `Proxy` contract instance on Ethereum.

use ethers::prelude::*;

abigen!(IBonsaiRelay, "$OUT_DIR/IBonsaiRelay.sol/IBonsaiRelay.json");
abigen!(BonsaiRelay, "$OUT_DIR/BonsaiRelay.sol/BonsaiRelay.json");
abigen!(
    BonsaiTestRelay,
    "$OUT_DIR/BonsaiTestRelay.sol/BonsaiTestRelay.json"
);

abigen!(
    IRiscZeroVerifier,
    "$OUT_DIR/IRiscZeroVerifier.sol/IRiscZeroVerifier.json"
);
abigen!(
    RiscZeroGroth16Verifier,
    "$OUT_DIR/RiscZeroGroth16Verifier.sol/RiscZeroGroth16Verifier.json"
);

pub mod testutils {
    use ethers::prelude::*;

    abigen!(Counter, "$OUT_DIR/Counter.sol/Counter.json");
    abigen!(Proxy, "$OUT_DIR/ProxyTest.sol/Proxy.json");
}
