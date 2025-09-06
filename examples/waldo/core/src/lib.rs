// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
