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

#[macro_use]
extern crate merkle_light_derive;

pub mod image;
pub mod merkle;

use serde::{Deserialize, Serialize};

/// Private input values to the image crop method.
#[derive(Debug, Serialize, Deserialize)]
pub struct PrivateInput {
    /// Merkle tree root committing to the full Where's Waldo image.
    pub root: merkle::Node,

    /// Width and height of the committed image.
    pub image_dimensions: (u32, u32),

    /// X and y location for the top left corner of the crop.
    pub crop_location: (u32, u32),

    /// Width and height of the cropped image.
    pub crop_dimensions: (u32, u32),

    /// Optional mask to apply to the image to filter out additional pixels from
    /// the crop area.
    pub mask: Option<Vec<u8>>,
}

/// Public journal values that will be committed by the image crop method.
#[derive(Debug, Serialize, Deserialize)]
pub struct Journal {
    pub subimage: Vec<u8>,

    /// Width and height of the resulting subimage.
    pub subimage_dimensions: (u32, u32),

    /// Merkle tree root of the committed image.
    /// Must be checked against the root of the image that was expected to be
    /// cropped.
    pub root: merkle::Node,

    /// Width and height of the committed image.
    /// Must be checked against the dimensions of the image that was expected to
    /// be cropped.
    pub image_dimensions: (u32, u32),
}
