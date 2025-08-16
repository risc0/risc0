// Copyright 2025 RISC Zero, Inc.
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

use image::{GenericImageView, imageops};
use risc0_zkvm::guest::env;
use waldo_core::{
    Journal, PrivateInput,
    image::{IMAGE_CHUNK_SIZE, ImageMask, ImageOracle},
};

fn main() {
    // Read a Merkle proof from the host.
    let input: PrivateInput = env::read();

    // Initialize a Merkle tree based vector oracle, supporting verified access to a
    // vector of data on the host. Use the oracle to access a range of elements
    // from the host.
    let oracle = ImageOracle::<{ IMAGE_CHUNK_SIZE }>::new(
        input.root,
        input.image_dimensions.0,
        input.image_dimensions.1,
    );

    let subimage = imageops::crop_imm(
        &oracle,
        input.crop_location.0,
        input.crop_location.1,
        input.crop_dimensions.0,
        input.crop_dimensions.1,
    )
    .to_image();

    // If a mask is provided, apply it to reveal less about the image.
    let subimage_masked = match input.mask {
        Some(mask_raw) => {
            let mask =
                ImageMask::from_raw(input.crop_dimensions.0, input.crop_dimensions.1, mask_raw)
                    .unwrap();
            mask.apply(subimage)
        }
        None => subimage,
    };

    // Collect the verified public information into the journal.
    let journal = Journal {
        root: *oracle.root(),
        image_dimensions: oracle.dimensions(),
        subimage_dimensions: subimage_masked.dimensions(),
        subimage: subimage_masked.into_raw(),
    };
    env::commit(&journal);
}
