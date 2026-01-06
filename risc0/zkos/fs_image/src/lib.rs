#![no_std]

use core::mem::size_of;

use bytemuck::{Pod, Zeroable};

pub const FS_MAGIC: [u8; 4] = *b"P9FS";
pub const FS_VERSION: u32 = 1;
pub const HEADER_SIZE: usize = size_of::<FilesystemImageHeader>();
pub const INODE_META_SIZE: usize = size_of::<INodeMeta>();

#[repr(C, align(8))]
#[derive(Copy, Clone, Pod, Zeroable, Debug)]
pub struct FilesystemImageHeader {
    pub magic: [u8; 4],
    pub version: u32,
    pub total_size: u32,
    pub num_inodes: u32,
    pub inode_table_offset: u32,
    pub data_blob_offset: u32,
    pub path_index_offset: u32,
    pub _padding: u32,
    pub root_inode: u64,
}

#[repr(C, align(8))]
#[derive(Copy, Clone, Pod, Zeroable, Debug)]
pub struct INodeMeta {
    pub qid_type: u8,
    pub _padding1: [u8; 3],
    pub qid_version: u32,
    pub qid_path: u64,
    pub mode: u32,
    pub uid: u32,
    pub gid: u32,
    pub _padding2: u32,
    pub nlink: u64,
    pub rdev: u64,
    pub size: u64,
    pub blksize: u64,
    pub blocks: u64,
    pub atime_sec: u64,
    pub atime_nsec: u64,
    pub mtime_sec: u64,
    pub mtime_nsec: u64,
    pub ctime_sec: u64,
    pub ctime_nsec: u64,
    pub btime_sec: u64,
    pub btime_nsec: u64,
    pub content_type: u8,
    pub _padding3: [u8; 3],
    pub content_offset: u32,
    pub content_length: u32,
    pub _padding4: u32,
}

