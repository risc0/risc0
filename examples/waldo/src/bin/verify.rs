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

use std::{error::Error, fs, path::PathBuf};

use clap::Parser;
use image::{GenericImageView, RgbImage, io::Reader as ImageReader};
use risc0_zkvm::Receipt;
use waldo_core::{
    Journal,
    image::{IMAGE_CHUNK_SIZE, ImageMerkleTree},
};
use waldo_methods::IMAGE_CROP_ID;

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Input file path to the full Where's Waldo image.
    /// Used to verify that the Waldo in the receipt actually came from this
    /// image.
    #[arg(short, long, value_parser, value_hint = clap::ValueHint::FilePath)]
    image: PathBuf,

    /// Input file path to fetch the receipt. Note that the receipt contains the
    /// cutout of waldo.
    #[arg(short = 'r', long, value_parser, default_value = "./receipt.bin", value_hint = clap::ValueHint::FilePath)]
    receipt: PathBuf,

    /// Output file path to save the cutout image of Waldo extracted from the
    /// receipt. SAFETY: Make sure to visually inspect the cutout and verify
    /// it really is Waldo and not some barber pole!
    #[arg(short = 'o', long, value_parser, default_value = "./waldo_cutout.png", value_hint = clap::ValueHint::FilePath)]
    waldo: PathBuf,

    /// Flag to disable displaying the Waldo cutout in the terminal.
    #[arg(long)]
    no_display: bool,
}

fn main() -> Result<(), Box<dyn Error>> {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    // Read the full Where's Waldo image from disk.
    let img = ImageReader::open(&args.image)?.decode()?;
    println!(
        "Read image at {} with size: {} x {}",
        &args.image.display(),
        img.width(),
        img.height()
    );

    // Construct a Merkle tree from the Where's Waldo image.
    let img_merkle_tree = ImageMerkleTree::<{ IMAGE_CHUNK_SIZE }>::new(&img);
    println!(
        "Created Merkle tree from image with root {:?}",
        img_merkle_tree.root(),
    );

    // Load and verify the receipt file.
    let receipt: Receipt = bincode::deserialize(&fs::read(&args.receipt)?)?;
    receipt.verify(IMAGE_CROP_ID)?;

    // Check consistency of the journal against the input Where's Waldo image.
    let journal: Journal = receipt.journal.decode()?;
    if journal.root != img_merkle_tree.root() {
        return Err(format!(
            "Image root in journal does not match the expected image: {:?} != {:?}",
            &journal.root,
            &img_merkle_tree.root(),
        )
        .into());
    }

    if journal.image_dimensions != img.dimensions() {
        return Err(format!(
            "Image dimensions in the journal do not match the expected image: {:?} != {:?}",
            journal.image_dimensions,
            img.dimensions(),
        )
        .into());
    }

    println!(
        "Verified receipt with {}x{} subimage",
        journal.subimage_dimensions.0, journal.subimage_dimensions.1
    );

    let subimage = RgbImage::from_raw(
        journal.subimage_dimensions.0,
        journal.subimage_dimensions.1,
        journal.subimage,
    )
    .ok_or("Failed to load the returned subimage bytes into an image")?;

    // Save the image to disk for the verifier to inspect.
    subimage.save(&args.waldo)?;
    println!("Saved Waldo cutout to {}", &args.waldo.display());

    if args.no_display {
        println!(
            "IMPORTANT: Verify that the cutout in {} contains Waldo.",
            &args.waldo.display()
        );
    } else {
        // Display the image in the terminal for them to see whether it's Waldo.
        let viuer_config = viuer::Config {
            absolute_offset: false,
            ..Default::default()
        };
        viuer::print_from_file(&args.waldo, &viuer_config)?;
        println!("Prover knows where this cutout is in the given image.");
        println!("Do you recognize this Waldo?");
    }

    Ok(())
}
