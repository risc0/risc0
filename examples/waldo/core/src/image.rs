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

use image::{DynamicImage, GrayImage, Rgb, RgbImage};
use serde::{Deserialize, Serialize};

use crate::merkle::{MerkleTree, Node};
use merkle_light::hash::Hashable;
use std::hash::Hasher;

/// Recommended default chunk size to use in the ImageMerkleTree and
/// ImageOracle.
pub const IMAGE_CHUNK_SIZE: u32 = 8;

// Chunk struct used internally to wrap the raw bytes and include a width value.
// Important for chunks at the edge of the image which may have a width or
// height of less than N.
#[derive(Debug, Clone, Serialize, Deserialize)]
struct ImageChunk {
    data: Vec<u8>,
    width: u32,
    height: u32,
}

impl<H: Hasher> Hashable<H> for ImageChunk {
    fn hash(&self, state: &mut H) {
        self.data.hash(state);
        self.width.hash(state);
        self.height.hash(state);
    }
}

impl From<RgbImage> for ImageChunk {
    fn from(image: RgbImage) -> Self {
        Self {
            width: image.width(),
            height: image.height(),
            data: image.into_raw(),
        }
    }
}

impl From<ImageChunk> for RgbImage {
    fn from(chunk: ImageChunk) -> RgbImage {
        RgbImage::from_raw(chunk.width, chunk.height, chunk.data).unwrap()
    }
}

/// Mask image that can be applied to an image to include or exclude pixels.
/// Pixel values are treated as booleans controlling whether or not the
/// corresponding pixel from the base image is included. A pixel value of 0
/// results in the corresponding pixel being masked out.
pub struct ImageMask(pub GrayImage);

impl ImageMask {
    /// Apply the mask to the given image, masking out any pixels in image where
    /// the mask contains a 0 value. Any mask pixel value of greater than
    /// zero passes the base pixel through.
    pub fn apply(&self, mut image: RgbImage) -> RgbImage {
        assert_eq!(image.dimensions(), self.0.dimensions());

        let zero_pixel: Rgb<u8> = [0, 0, 0].into();
        for y in 0..image.height() {
            for x in 0..image.width() {
                let m = self.0.get_pixel(x, y);
                if m.0[0] == 0 {
                    image.put_pixel(x, y, zero_pixel);
                }
            }
        }
        image
    }

    pub fn into_raw(self) -> Vec<u8> {
        self.0.into_raw()
    }

    pub fn dimensions(&self) -> (u32, u32) {
        self.0.dimensions()
    }

    pub fn from_raw(width: u32, height: u32, data: Vec<u8>) -> Option<Self> {
        GrayImage::from_raw(width, height, data).map(|img| img.into())
    }
}

impl From<DynamicImage> for ImageMask {
    fn from(image: DynamicImage) -> Self {
        Self(image.into_luma8())
    }
}

impl From<GrayImage> for ImageMask {
    fn from(image: GrayImage) -> Self {
        Self(image)
    }
}

/// ImageMerkleTree is a merklization of an image, constructed with leaf
/// elements of NxN square chunks, traversed in left-to-right and top-to-bottom
/// order.
///
/// Chunks on the right and bottom boundaries will be incomplete if the width or
/// height cannot be divided by N. At the right edge, the width of the chunks
/// will be truncated and on the bottom edge the height will be truncated.
pub struct ImageMerkleTree<const N: u32>(MerkleTree<ImageChunk>);

impl<const N: u32> ImageMerkleTree<N> {
    pub fn new(image: &DynamicImage) -> Self {
        let chunks: Vec<ImageChunk> = {
            (0..image.height())
                .step_by(usize::try_from(N).unwrap())
                .flat_map(|y| {
                    (0..image.width())
                        .step_by(usize::try_from(N).unwrap())
                        .map(move |x| image.crop_imm(x, y, N, N).into_rgb8().into())
                })
                .collect()
        };

        Self(MerkleTree::new(chunks))
    }

    pub fn root(&self) -> Node {
        self.0.root()
    }

    #[cfg(not(target_os = "zkvm"))]
    pub fn vector_oracle_callback(
        &self,
    ) -> impl Fn(risc0_zkvm::Bytes) -> risc0_zkvm::Result<risc0_zkvm::Bytes> + '_ {
        self.0.vector_oracle_callback()
    }
}

#[cfg(target_os = "zkvm")]
mod zkvm {
    use divrem::{DivCeil, DivRem};
    use elsa::FrozenBTreeMap;
    use image::{GenericImageView, Rgb, RgbImage};

    use super::ImageChunk;
    use crate::merkle::{Node, VectorOracle};

    /// ImageOracle provides verified access to an image held by the host and
    /// implements image::GenericImageView so that functions from the image
    /// crate, and those built against it's API, can be applied to the
    /// ImageOracle.
    pub struct ImageOracle<const N: u32> {
        chunks: VectorOracle<ImageChunk>,

        // Width and height of the image in pixels.
        width: u32,
        height: u32,

        // Fields used internally for precomputation and caching.
        width_chunks: u32,
        cache: FrozenBTreeMap<(u32, u32), Box<RgbImage>>,
    }

    impl<const N: u32> ImageOracle<N> {
        pub fn new(root: Node, width: u32, height: u32) -> Self {
            Self {
                chunks: VectorOracle::new(root),
                width,
                height,
                width_chunks: DivCeil::div_ceil(width, N),
                cache: Default::default(),
            }
        }

        /// Memoized method for getting chunks of the image. Inputs x and y are
        /// chunk coordinates.
        fn get_chunk(&self, x: u32, y: u32) -> &RgbImage {
            // Check that the given x  if within the bounds of the width. No need to check y
            // since if y is out of bounds the VectorOracle query will be out
            // of bounds.
            match self.cache.get(&(x, y)) {
                Some(chunk) => chunk,
                None => {
                    assert!(x < self.width_chunks);

                    let chunk = self
                        .chunks
                        .get(usize::try_from(y * self.width_chunks + x).unwrap());
                    self.cache.insert((x, y), Box::new(RgbImage::from(chunk)));
                    self.cache.get(&(x, y)).unwrap()
                }
            }
        }

        pub fn root(&self) -> &Node {
            self.chunks.root()
        }
    }

    impl<const N: u32> GenericImageView for ImageOracle<N> {
        type Pixel = Rgb<u8>;

        fn dimensions(&self) -> (u32, u32) {
            (self.width, self.height)
        }

        fn bounds(&self) -> (u32, u32, u32, u32) {
            (0, 0, self.width, self.height)
        }

        #[inline(always)]
        fn get_pixel(&self, x: u32, y: u32) -> Self::Pixel {
            assert!(self.in_bounds(x, y));

            // Calculate split x and y into the chunk selector portion and offset.
            let (x_chunk, x_offset) = DivRem::div_rem(x, N);
            let (y_chunk, y_offset) = DivRem::div_rem(y, N);

            let chunk = &self.get_chunk(x_chunk, y_chunk);
            *chunk.get_pixel(x_offset, y_offset)
        }
    }
}

#[cfg(target_os = "zkvm")]
pub use crate::image::zkvm::*;
