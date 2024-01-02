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

use image::{io::Reader as ImageReader, GenericImageView};
use risc0_zkvm::ExecutorEnv;
use waldo_core::{
    image::{ImageMask, ImageMerkleTree, IMAGE_CHUNK_SIZE},
    merkle::SYS_VECTOR_ORACLE,
    PrivateInput,
};

use crate::{exec, CycleCounter, Metrics};

pub struct Job {}

impl CycleCounter for Job {
    const NAME: &'static str = "waldo";
    const METHOD_ELF: &'static [u8] = waldo_methods::IMAGE_CROP_ELF;

    fn run() -> Metrics {
        // Read the image from disk.
        let img = ImageReader::open("../waldo/waldo.webp")
            .unwrap()
            .decode()
            .unwrap();
        let crop_location: (u32, u32) = (1150, 291);
        let crop_dimensions: (u32, u32) = (58, 70);

        // Read the image mask from disk.
        let mask: ImageMask = ImageReader::open("../waldo/waldo_mask.png")
            .unwrap()
            .decode()
            .unwrap()
            .into();

        // Construct a Merkle tree from the full Where's Waldo image.
        let img_merkle_tree = ImageMerkleTree::<{ IMAGE_CHUNK_SIZE }>::new(&img);

        // Give the private input to the guest, including Waldo's location.
        let input = PrivateInput {
            root: img_merkle_tree.root(),
            image_dimensions: img.dimensions(),
            mask: Some(mask.into_raw()),
            crop_location,
            crop_dimensions,
        };

        let env = ExecutorEnv::builder()
            .write(&input)
            .unwrap()
            .io_callback(SYS_VECTOR_ORACLE, img_merkle_tree.vector_oracle_callback())
            .build()
            .unwrap();

        exec(Self::NAME, Self::METHOD_ELF, env)
    }
}
