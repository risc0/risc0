pub(crate) const GPIO_SHA: *mut *const SHADescriptor = 0x001C_0000 as _;
pub(crate) const GPIO_READ: *mut *const IoDescriptor = 0x001C_0004 as _;
pub(crate) const GPIO_WRITE: *mut *const IoDescriptor = 0x001C_0008 as _;
pub(crate) const GPIO_FAULT: *mut *const FaultDescriptor = 0x001C_000C as _;
pub(crate) const GPIO_LOG: *mut *const IoDescriptor = 0x001C_0010 as _;

pub(crate) const GPIO_DESC_IO: *mut IoDescriptor = 0x001D_0000 as _;
pub(crate) const GPIO_DESC_FAULT: *mut FaultDescriptor = 0x001D_0000 as _;

#[repr(C)]
pub(crate) struct IoDescriptor {
    pub size: usize,
    pub addr: usize,
}

#[repr(C)]
pub(crate) struct FaultDescriptor {
    pub addr: usize,
}

#[repr(C)]
pub(crate) struct SHADescriptor {
    pub type_count: usize,
    pub idx: usize,
    pub source: usize,
    pub digest: usize,
}
