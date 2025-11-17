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

use clap::Parser;
use risc0_binfmt::{ByteAddr, MemoryImage, Program, ProgramBinary};
use std::collections::BTreeMap;
use std::path::PathBuf;

pub const USER_START_ADDR: ByteAddr = ByteAddr(0x0001_0000);

// Memory layout constants
// Stack grows DOWN from top, so heap must end BEFORE stack top
const KERNEL_STACK_ADDR: u32 = 0xfff00000;
const KERNEL_STACK_MAX_SIZE: u32 = 1024 * 1024; // Max 1MB stack growth
const KERNEL_HEAP_STACK_GAP: u32 = 1024 * 1024; // 1MB safety gap
const KERNEL_HEAP_SIZE: u32 = 16 * 1024 * 1024; // 16MB fixed
                                                // Heap ends before stack bottom: stack_top - stack_size - gap
const KERNEL_HEAP_END: u32 = KERNEL_STACK_ADDR - KERNEL_STACK_MAX_SIZE - KERNEL_HEAP_STACK_GAP;
const KERNEL_HEAP_START: u32 = KERNEL_HEAP_END - KERNEL_HEAP_SIZE; // 0xfed00000
const FS_IMAGE_ADDR_PTR: u32 = 0xffff_3030; // Where we store the FS address

// Zero-copy filesystem image builder shared with the kernel
mod filesystem_image {
    use super::*;
    use risc0_zkos_fs::{
        FilesystemImageHeader, INodeMeta, FS_MAGIC, FS_VERSION, HEADER_SIZE, INODE_META_SIZE,
    };
    use std::fs;
    use std::io;

    /// Build a zero-copy filesystem image from a directory
    pub fn build_from_directory(root_path: &PathBuf) -> io::Result<Vec<u8>> {
        println!("Building zero-copy filesystem from {:?}", root_path);
        debug_assert_eq!(core::mem::size_of::<FilesystemImageHeader>(), HEADER_SIZE);
        debug_assert_eq!(core::mem::size_of::<INodeMeta>(), INODE_META_SIZE);

        let mut inodes = BTreeMap::new();
        let mut paths = BTreeMap::new();
        let mut next_inode = 2u64; // Start at 2, root is 1
        let mut data_blob = Vec::new();

        // Create root directory entry
        let root_meta = create_dir_meta(1, 0o040755, 0, 0, &[]);
        inodes.insert(1u64, root_meta);
        paths.insert("/".to_string(), 1u64);

        // Walk directory tree
        walk_directory(
            root_path,
            "/",
            &mut inodes,
            &mut paths,
            &mut next_inode,
            &mut data_blob,
        )?;

        // Build the final image
        let image = build_image(inodes, paths, data_blob);

        println!(
            "Filesystem image built: {} bytes, {} inodes",
            image.len(),
            next_inode - 1
        );
        Ok(image)
    }

    fn walk_directory(
        fs_path: &PathBuf,
        vfs_path: &str,
        inodes: &mut BTreeMap<u64, INodeMeta>,
        paths: &mut BTreeMap<String, u64>,
        next_inode: &mut u64,
        data_blob: &mut Vec<u8>,
    ) -> io::Result<()> {
        let entries = fs::read_dir(fs_path)?;
        let mut dir_entries = Vec::new();

        for entry in entries {
            let entry = entry?;
            let file_name = entry.file_name().to_string_lossy().to_string();
            let metadata = entry.metadata()?;
            let child_path = if vfs_path == "/" {
                format!("/{}", file_name)
            } else {
                format!("{}/{}", vfs_path, file_name)
            };

            let inode_num = *next_inode;
            *next_inode += 1;

            let is_dir = metadata.is_dir();
            let is_symlink = metadata.is_symlink();

            let (content_type, qid_type) = if is_dir {
                (1u8, 0x80u8) // Directory
            } else if is_symlink {
                (2u8, 0x02u8) // Symlink
            } else {
                (0u8, 0x00u8) // Regular file
            };

            // Check for overflow: data_blob.len() must fit in u32
            let content_offset = data_blob.len().try_into().map_err(|_| {
                io::Error::new(
                    io::ErrorKind::InvalidData,
                    format!("Data blob too large: {} bytes (max: {})", data_blob.len(), u32::MAX),
                )
            })?;
            let mut content_length = 0u32;

            let mode = if metadata.is_dir() {
                0o040755
            } else if metadata.is_symlink() {
                0o120777
            } else {
                0o100644
            };

            let mut meta = INodeMeta {
                qid_type,
                _padding1: [0; 3],
                qid_version: 0,
                qid_path: inode_num,
                mode,
                uid: 0,
                gid: 0,
                _padding2: 0,
                nlink: if metadata.is_dir() { 2 } else { 1 },
                rdev: 0,
                size: metadata.len(),
                blksize: 4096,
                blocks: metadata.len().checked_add(511)
                    .and_then(|n| n.checked_div(512))
                    .unwrap_or(u64::MAX), // Safe fallback for huge files
                atime_sec: 0,
                atime_nsec: 0,
                mtime_sec: 0,
                mtime_nsec: 0,
                ctime_sec: 0,
                ctime_nsec: 0,
                btime_sec: 0,
                btime_nsec: 0,
                content_type,
                _padding3: [0; 3],
                content_offset,
                content_length,
                _padding4: 0,
            };

            if is_dir {
                // Insert the placeholder metadata before recursing so the child walk can
                // update content_offset/content_length for this directory.
                inodes.insert(inode_num, meta);
                paths.insert(child_path.clone(), inode_num);

                walk_directory(
                    &entry.path(),
                    &child_path,
                    inodes,
                    paths,
                    next_inode,
                    data_blob,
                )?;
            } else {
                if is_symlink {
                    // Read symlink target
                    let target = fs::read_link(entry.path())?;
                    let target_str = target.to_string_lossy();
                    let target_bytes = target_str.as_bytes();
                    // Check for overflow: symlink target must fit in u32
                    if target_bytes.len() > u32::MAX as usize {
                        return Err(io::Error::new(
                            io::ErrorKind::InvalidData,
                            format!("Symlink target too large: {} bytes (max: {})", target_bytes.len(), u32::MAX),
                        ));
                    }
                    data_blob.extend_from_slice(target_bytes);
                    content_length = target_bytes.len() as u32;
                } else {
                    // Regular file - read content
                    let file_data = fs::read(entry.path())?;
                    // Check for overflow: file content must fit in u32
                    if file_data.len() > u32::MAX as usize {
                        return Err(io::Error::new(
                            io::ErrorKind::InvalidData,
                            format!("File too large: {} bytes (max: {})", file_data.len(), u32::MAX),
                        ));
                    }
                    data_blob.extend_from_slice(&file_data);
                    content_length = file_data.len() as u32;
                }

                meta.content_length = content_length;
                inodes.insert(inode_num, meta);
                paths.insert(child_path.clone(), inode_num);
            }

            // Store for directory entry
            dir_entries.push((file_name, inode_num, qid_type));
        }

        // Update directory content with entries
        if let Some(dir_inode_num) = paths.get(vfs_path) {
            // Check for overflow: data_blob.len() must fit in u32
            let content_offset = data_blob.len().try_into().map_err(|_| {
                io::Error::new(
                    io::ErrorKind::InvalidData,
                    format!("Data blob too large: {} bytes (max: {})", data_blob.len(), u32::MAX),
                )
            })?;
            let dir_data = serialize_dir_entries(&dir_entries);
            // Check for overflow: directory data must fit in u32
            if dir_data.len() > u32::MAX as usize {
                return Err(io::Error::new(
                    io::ErrorKind::InvalidData,
                    format!("Directory data too large: {} bytes (max: {})", dir_data.len(), u32::MAX),
                ));
            }
            data_blob.extend_from_slice(&dir_data);

            if let Some(meta) = inodes.get_mut(dir_inode_num) {
                meta.content_offset = content_offset;
                meta.content_length = dir_data.len() as u32;
            }
        }

        Ok(())
    }

    fn create_dir_meta(inode: u64, mode: u32, uid: u32, gid: u32, content: &[u8]) -> INodeMeta {
        INodeMeta {
            qid_type: 0x80,
            _padding1: [0; 3],
            qid_version: 0,
            qid_path: inode,
            mode,
            uid,
            gid,
            _padding2: 0,
            nlink: 2,
            rdev: 0,
            size: 4096,
            blksize: 4096,
            blocks: 8,
            atime_sec: 0,
            atime_nsec: 0,
            mtime_sec: 0,
            mtime_nsec: 0,
            ctime_sec: 0,
            ctime_nsec: 0,
            btime_sec: 0,
            btime_nsec: 0,
            content_type: 1,
            _padding3: [0; 3],
            content_offset: 0,
            content_length: content.len() as u32,
            _padding4: 0,
        }
    }

    fn serialize_dir_entries(entries: &[(String, u64, u8)]) -> Vec<u8> {
        let mut data = Vec::new();

        // Number of entries - check for overflow
        let num_entries = entries.len().try_into().unwrap_or(u32::MAX);
        data.extend_from_slice(&num_entries.to_le_bytes());

        for (name, inode, qtype) in entries {
            // QID (13 bytes)
            data.push(*qtype);
            data.extend_from_slice(&0u32.to_le_bytes()); // version
            data.extend_from_slice(&inode.to_le_bytes()); // path

            // Entry type
            let dt_type = if *qtype & 0x80 != 0 {
                4
            } else if *qtype & 0x02 != 0 {
                10
            } else {
                8
            };
            data.push(dt_type);

            // Inode number
            data.extend_from_slice(&inode.to_le_bytes());

            // Name - check for overflow: filename must fit in u16
            let name_len = name.len().min(u16::MAX as usize);
            data.extend_from_slice(&(name_len as u16).to_le_bytes());
            data.extend_from_slice(&name.as_bytes()[..name_len]);
        }

        data
    }

    fn build_image(
        inodes: BTreeMap<u64, INodeMeta>,
        paths: BTreeMap<String, u64>,
        data_blob: Vec<u8>,
    ) -> Vec<u8> {
        let mut image = Vec::new();

        // Create header (inode_table_offset will be updated after padding)
        // CRITICAL: num_inodes must match max_inode (not just inodes.len())
        // because p9_in_memory.rs expects a dense table numbered 1..=num_inodes
        let max_inode = inodes.keys().max().copied().unwrap_or(0);
        let num_inodes = max_inode.try_into().unwrap_or_else(|_| {
            panic!("Too many inodes: {} (max: {})", max_inode, u32::MAX);
        });
        
        let header = FilesystemImageHeader {
            magic: FS_MAGIC,
            version: FS_VERSION,
            total_size: 0, // Will update
            num_inodes,
            inode_table_offset: 0, // Will update after padding
            data_blob_offset: 0,   // Will update
            path_index_offset: 0,  // Will update
            _padding: 0,
            root_inode: 1,
        };

        // Write header (placeholder)
        image.extend_from_slice(bytemuck::bytes_of(&header));

        // CRITICAL: Ensure inode table is 8-byte aligned for bytemuck::cast_slice
        // Header is 40 bytes (8-byte aligned), so inode table should already be aligned,
        // but add explicit padding to be safe
        const INODE_ALIGNMENT: usize = 8; // INodeMeta requires 8-byte alignment
        let padding_needed = (INODE_ALIGNMENT - (image.len() % INODE_ALIGNMENT)) % INODE_ALIGNMENT;
        if padding_needed > 0 {
            image.extend_from_slice(&vec![0u8; padding_needed]);
            eprintln!(
                "Added {} bytes padding after header to align inode table",
                padding_needed
            );
        }

        // Verify alignment
        debug_assert_eq!(
            image.len() % INODE_ALIGNMENT,
            0,
            "Inode table must be 8-byte aligned for bytemuck::cast_slice"
        );

        // Record actual inode table offset (after padding)
        // Check for overflow: image.len() must fit in u32
        let inode_table_offset = image.len().try_into().unwrap_or_else(|_| {
            panic!("Image too large: {} bytes (max: {})", image.len(), u32::MAX);
        });

        // Write inode table - CRITICAL: Write inodes in order 1..=max_inode
        // This ensures the inode table is dense and matches what p9_in_memory.rs expects
        // p9_in_memory.rs uses (inode_num - 1) as the index, so inodes must be numbered 1..=num_inodes
        let inode_table_start = image.len();
        let max_inode = inodes.keys().max().copied().unwrap_or(0);
        
        // Verify that inodes are dense (no gaps expected, but handle defensively)
        if max_inode != inodes.len() as u64 {
            eprintln!(
                "WARNING: Inode numbers are not dense: max_inode={}, num_inodes={}",
                max_inode, inodes.len()
            );
        }
        
        // Write inodes in order 1..=max_inode to ensure dense table
        for i in 1..=max_inode {
            if let Some(meta) = inodes.get(&i) {
                image.extend_from_slice(bytemuck::bytes_of(meta));
            } else {
                // This should never happen if inodes are allocated sequentially,
                // but handle it defensively to prevent memory corruption in p9_in_memory.rs
                eprintln!("ERROR: Missing inode {} in table! This will cause memory corruption!", i);
                panic!("Inode table has gaps - inode {} is missing. This will cause out-of-bounds access in p9_in_memory.rs", i);
            }
        }

        // Verify inode table alignment
        debug_assert_eq!(
            inode_table_start % INODE_ALIGNMENT,
            0,
            "Inode table start must be 8-byte aligned"
        );

        // Write path index
        // Check for overflow: image.len() must fit in u32
        let path_index_offset = image.len().try_into().unwrap_or_else(|_| {
            panic!("Image too large for path index: {} bytes (max: {})", image.len(), u32::MAX);
        });
        
        // Check for overflow: paths.len() must fit in u32
        let num_paths = paths.len().try_into().unwrap_or(u32::MAX);
        image.extend_from_slice(&num_paths.to_le_bytes());
        
        for (path, inode_num) in &paths {
            // Check for overflow: path.len() must fit in u16
            let path_len = path.len().min(u16::MAX as usize);
            image.extend_from_slice(&(path_len as u16).to_le_bytes());
            image.extend_from_slice(&path.as_bytes()[..path_len]);
            image.extend_from_slice(&inode_num.to_le_bytes());
        }

        // Write data blob
        // Check for overflow: image.len() must fit in u32
        let data_blob_offset = image.len().try_into().unwrap_or_else(|_| {
            panic!("Image too large for data blob: {} bytes (max: {})", image.len(), u32::MAX);
        });
        image.extend_from_slice(&data_blob);

        // Update header with correct offsets
        // Check for overflow: image.len() must fit in u32
        let total_size = image.len().try_into().unwrap_or_else(|_| {
            panic!("Image too large: {} bytes (max: {})", image.len(), u32::MAX);
        });
        let mut header =
            bytemuck::pod_read_unaligned::<FilesystemImageHeader>(&image[..HEADER_SIZE]);
        header.total_size = total_size;
        header.inode_table_offset = inode_table_offset; // Update with actual offset after padding
        header.path_index_offset = path_index_offset;
        header.data_blob_offset = data_blob_offset;

        image[..HEADER_SIZE].copy_from_slice(bytemuck::bytes_of(&header));

        image
    }
}

/// Embed filesystem into kernel program
fn embed_filesystem(
    kernel_program: &mut Program,
    root_dir: &PathBuf,
) -> Result<(), Box<dyn std::error::Error>> {
    println!("Embedding zero-copy filesystem from {:?}", root_dir);

    // Build filesystem image
    let fs_image = filesystem_image::build_from_directory(root_dir)
        .map_err(|e| format!("Failed to build filesystem image: {}", e))?;

    let fs_size = fs_image.len();
    println!(
        "Filesystem image size: {} bytes ({:.2} MB)",
        fs_size,
        fs_size as f64 / (1024.0 * 1024.0)
    );

    // Calculate where to place the filesystem (below fixed kernel heap, 4KB aligned)
    // Memory layout: Stack | Heap (16MB fixed) | FS (variable) | User Space
    // CRITICAL: Must be 4KB aligned for zero-copy access with bytemuck
    const PAGE_SIZE: u32 = 4096; // 4KB
    const PAGE_MASK: u32 = !(PAGE_SIZE - 1); // 0xfffff000 (clears bottom 12 bits)

    // Calculate raw address (before alignment)
    let fs_addr_raw = KERNEL_HEAP_START - fs_size as u32;

    // Align DOWN to 4KB boundary (clears bottom 12 bits)
    let fs_addr = (fs_addr_raw & PAGE_MASK) as u32;

    // Verify alignment is correct
    if (fs_addr & (PAGE_SIZE - 1)) != 0 {
        return Err(format!(
            "FATAL: Alignment calculation failed! FS addr: 0x{:08x}, offset: 0x{:03x}",
            fs_addr,
            fs_addr & (PAGE_SIZE - 1)
        )
        .into());
    }

    println!("Memory layout:");
    println!("  Stack:        0x{:08x}", KERNEL_STACK_ADDR);
    println!("  Heap start:   0x{:08x} (16 MB fixed)", KERNEL_HEAP_START);
    println!(
        "  FS start:     0x{:08x} ({:.2} MB) [4KB aligned]",
        fs_addr,
        fs_size as f64 / (1024.0 * 1024.0)
    );
    println!("  FS end:       0x{:08x}", fs_addr + fs_size as u32);

    // Log alignment info
    if fs_addr != fs_addr_raw {
        let alignment_adjustment = fs_addr_raw - fs_addr;
        println!(
            "  Alignment: Adjusted DOWN by {} bytes to 4KB boundary",
            alignment_adjustment
        );
    } else {
        println!("  Alignment: Already 4KB aligned (no adjustment needed)");
    }

    // Debug: show first 16 bytes of FS image
    println!(
        "  First 16 bytes of FS image: {:02x?}",
        &fs_image[..16.min(fs_image.len())]
    );

    // Write filesystem image into memory as u32 words
    // Pad to word boundary if needed
    let mut fs_image_padded = fs_image.clone();
    while fs_image_padded.len() % 4 != 0 {
        fs_image_padded.push(0);
    }

    // CRITICAL: Use padded size for all calculations to avoid heap overlap!
    let fs_size_padded = fs_image_padded.len() as u32;

    // CRITICAL: Reserve minimum gap between FS and heap for safety
    // This prevents accidental overlap and allows for alignment adjustments
    const MIN_FS_HEAP_GAP: u32 = 4 * 1024; // 4KB minimum gap

    // Recalculate placement with padded size AND minimum gap
    // Must maintain 4KB alignment
    let fs_addr_raw_final = KERNEL_HEAP_START - fs_size_padded - MIN_FS_HEAP_GAP;
    let fs_addr_final = (fs_addr_raw_final & PAGE_MASK) as u32;

    // Verify final alignment
    if (fs_addr_final & (PAGE_SIZE - 1)) != 0 {
        return Err(format!(
            "FATAL: Final alignment calculation failed! FS addr: 0x{:08x}, offset: 0x{:03x}",
            fs_addr_final,
            fs_addr_final & (PAGE_SIZE - 1)
        )
        .into());
    }

    if fs_addr_final != fs_addr {
        eprintln!("WARNING: FS placement recalculated due to padding!");
        eprintln!("  Original addr: 0x{:08x} (size: {})", fs_addr, fs_size);
        eprintln!(
            "  Final addr:    0x{:08x} (padded size: {})",
            fs_addr_final, fs_size_padded
        );
    }

    let fs_addr = fs_addr_final;

    println!(
        "  Writing {} words starting at 0x{:08x}",
        fs_image_padded.len() / 4,
        fs_addr
    );

    println!("  FS end (padded): 0x{:08x}", fs_addr + fs_size_padded);

    // Verify FS placement doesn't overlap with heap
    let fs_end = fs_addr + fs_size_padded;
    if fs_end > KERNEL_HEAP_START {
        return Err(format!(
            "FATAL: Filesystem (padded) extends into kernel heap! FS end: 0x{:08x}, Heap start: 0x{:08x}",
            fs_end, KERNEL_HEAP_START
        ).into());
    }

    // Verify minimum gap (should always pass since we reserved it in calculation)
    let gap = KERNEL_HEAP_START - fs_end;
    if gap < MIN_FS_HEAP_GAP {
        return Err(format!(
            "FATAL: Filesystem too close to heap! Gap: {} bytes (minimum: {} bytes). FS end: 0x{:08x}, Heap start: 0x{:08x}",
            gap, MIN_FS_HEAP_GAP, fs_end, KERNEL_HEAP_START
        ).into());
    }

    println!(
        "  ✓ Gap to heap: {} KB (minimum: {} KB)",
        gap / 1024,
        MIN_FS_HEAP_GAP / 1024
    );

    // Verify FS placement doesn't overlap with stack
    // Stack grows DOWN from KERNEL_STACK_ADDR, worst case bottom is KERNEL_STACK_ADDR - KERNEL_STACK_MAX_SIZE
    let stack_bottom = KERNEL_STACK_ADDR - KERNEL_STACK_MAX_SIZE;
    if fs_end >= stack_bottom {
        return Err(format!(
            "FATAL: Filesystem overlaps with stack! FS end: 0x{:08x}, Stack bottom: 0x{:08x}",
            fs_end, stack_bottom
        )
        .into());
    }

    // Log gap information
    let gap_to_heap = KERNEL_HEAP_START - fs_end;
    if gap_to_heap == 0 {
        println!("  ✓ FS ends exactly at heap start (touching, OK)");
    } else {
        println!("  ✓ Gap between FS and heap: {} KB", gap_to_heap / 1024);
    }

    // Verify alignment
    if (fs_addr & 0xfff) != 0 {
        return Err(format!(
            "FATAL: Filesystem address not 4KB aligned! FS start: 0x{:08x}",
            fs_addr
        )
        .into());
    }

    for (i, chunk) in fs_image_padded.chunks_exact(4).enumerate() {
        let word = u32::from_le_bytes([chunk[0], chunk[1], chunk[2], chunk[3]]);
        let addr = fs_addr + (i as u32 * 4);
        kernel_program.write_u32(addr, word);
    }

    println!("  Wrote {} bytes to memory", fs_image_padded.len());

    // Write the filesystem address to FS_IMAGE_ADDR_PTR
    kernel_program.write_u32(FS_IMAGE_ADDR_PTR, fs_addr);

    println!(
        "Filesystem address pointer written to: 0x{:08x} = 0x{:08x}",
        FS_IMAGE_ADDR_PTR, fs_addr
    );
    println!(
        "Heap will start at approximately: 0x{:08x}",
        (fs_addr + fs_size_padded + 0xfff) & !0xfff
    );

    // Debug: verify what we wrote
    if let Some(read_back) = kernel_program.read_u32(&FS_IMAGE_ADDR_PTR) {
        if read_back != fs_addr {
            eprintln!(
                "WARNING: Read back 0x{:08x}, expected 0x{:08x}",
                read_back, fs_addr
            );
        } else {
            println!("Verified: FS address pointer contains 0x{:08x}", read_back);
        }
    } else {
        eprintln!("WARNING: Could not read back FS address pointer!");
    }

    Ok(())
}

#[derive(Parser)]
#[command(name = "elf-to-bin")]
#[command(
    about = "A simple tool to combine a guest ELF with a kernel ELF into a .bin file, or create a MemoryImage from just a kernel ELF"
)]
struct Args {
    /// Path to the guest ELF file (optional)
    #[arg(short, long)]
    interp_elf: Option<PathBuf>,

    #[arg(short, long)]
    guest_elf: Option<PathBuf>,

    /// Path to the kernel ELF file
    #[arg(short, long)]
    kernel_elf: PathBuf,

    /// Output path for the combined .bin file
    #[arg(short, long)]
    output: PathBuf,

    /// Root directory to embed as zero-copy P9 filesystem (optional)
    #[arg(short, long)]
    root: Option<PathBuf>,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args = Args::parse();

    // Read the kernel ELF
    let kernel_elf = std::fs::read(&args.kernel_elf).map_err(|e| {
        format!(
            "Failed to read kernel ELF from {:?}: {}",
            args.kernel_elf, e
        )
    })?;

    let bin_data = if let Some(interp_elf_path) = &args.interp_elf {
        if let Some(guest_elf_path) = &args.guest_elf {
            let kernel_elf = std::fs::read(&args.kernel_elf).map_err(|e| {
                format!(
                    "Failed to read kernel ELF from {:?}: {}",
                    args.kernel_elf, e
                )
            })?;
            let mut kernel_program = Program::load_elf(&kernel_elf, u32::MAX)
                .map_err(|e| format!("Failed to load kernel ELF: {}", e))?;

            // Handle --root parameter: embed zero-copy filesystem
            if let Some(root_dir) = &args.root {
                embed_filesystem(&mut kernel_program, root_dir)?;
            } else {
                // No filesystem - write 0 to indicate no FS
                kernel_program.write_u32(FS_IMAGE_ADDR_PTR, 0);
            }

            let interp_elf = std::fs::read(interp_elf_path).map_err(|e| {
                format!("Failed to read guest ELF from {:?}: {}", interp_elf_path, e)
            })?;
            let guest_elf = std::fs::read(guest_elf_path).map_err(|e| {
                format!("Failed to read guest ELF from {:?}: {}", guest_elf_path, e)
            })?;

            const USER_MAX_MEM: u32 = 0x4000_0000;
            let elf = Program::load_elf_dyn(&guest_elf, USER_MAX_MEM, &interp_elf).map_err(|e| {
                format!("Failed to read guest ELF from {:?}: {}", guest_elf_path, e)
            })?;
            let memory_image = MemoryImage::new_dyn(elf, kernel_program);
            bincode::serialize(&memory_image)
                .map_err(|e| format!("Failed to serialize MemoryImage: {}", e))?
        } else {
            panic!("Guest ELF path is required");
        }
    } else if let Some(guest_elf_path) = &args.guest_elf {
        let guest_elf = std::fs::read(guest_elf_path)
            .map_err(|e| format!("Failed to read guest ELF from {:?}: {}", guest_elf_path, e))?;

        // Create the combined binary
        let binary = ProgramBinary::new(&guest_elf, &kernel_elf);
        binary.encode()
    } else {
        // Create MemoryImage from kernel ELF only
        let mut kernel_program = Program::load_elf(&kernel_elf, u32::MAX)
            .map_err(|e| format!("Failed to load kernel ELF: {}", e))?;
        kernel_program.write_u32(USER_START_ADDR.0, 0);

        // Handle --root parameter: embed zero-copy filesystem
        if let Some(root_dir) = &args.root {
            embed_filesystem(&mut kernel_program, root_dir)?;
        } else {
            // No filesystem - write 0 to indicate no FS
            kernel_program.write_u32(FS_IMAGE_ADDR_PTR, 0);
        }

        let memory_image = MemoryImage::new_kernel(kernel_program);
        // Serialize the MemoryImage
        bincode::serialize(&memory_image)
            .map_err(|e| format!("Failed to serialize MemoryImage: {}", e))?
    };

    // Write the output file
    std::fs::write(&args.output, &bin_data)
        .map_err(|e| format!("Failed to write output to {:?}: {}", args.output, e))?;

    if let Some(guest_elf_path) = &args.guest_elf {
        println!(
            "Successfully created {:?} from guest ELF {:?} and kernel ELF {:?}",
            args.output, guest_elf_path, args.kernel_elf
        );
    } else {
        println!(
            "Successfully created {:?} from kernel ELF {:?} (MemoryImage)",
            args.output, args.kernel_elf
        );
    }
    println!("Output size: {} bytes", bin_data.len());

    Ok(())
}
