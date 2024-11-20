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

// Macros used by code generation.  They all start with "codegen_" to
// minimimze namespace pollution since they appear in the top of the
// library.

#[macro_export]
macro_rules! codegen_make_tap {
    ($regGroupId:literal, $offset:literal, $back:literal) => {
        paste::paste! {
            Tap {
                group: $regGroupId,
                pos: $offset,
                back: $back,
            }
        }
    };
}

#[macro_export]
macro_rules! codegen_invoke_extern {
    ($ctx:ident, $name:ident $(, $exprs:expr)*) => {
        $ctx.$name($($exprs),*)?
    }
}

#[macro_export]
macro_rules! codegen_set_field {
    ($field:ident) => {
        paste::paste! {
            pub type CircuitField = risc0_core::field::[<$field:snake>]::$field;
            pub type Val = <CircuitField as risc0_core::field::Field>::Elem;
            pub type ExtVal = <CircuitField as risc0_core::field::Field>::ExtElem;
            pub type MixState = risc0_zkp::adapter::MixState<ExtVal>;
            pub type PolyMix = ExtVal;
        }
    };
}

#[macro_export]
macro_rules! codegen_load {
    ($ref:expr, $back:expr) => {
        paste::paste! {
            load($ref, $back)
        }
    };
}

#[macro_export]
macro_rules! codegen_load_as_ext {
    ($ref:expr, $back:expr) => {
        paste::paste! {
            ExtVal::from($crate::codegen_load!($ref, $back))
        }
    };
}

#[macro_export]
macro_rules! codegen_load_ext {
    ($ref:expr, $back:expr) => {
        paste::paste! {
            load_ext($ref, $back)
        }
    };
}

#[macro_export]
macro_rules! codegen_store {
    ($ref:expr, $val:expr) => {
        paste::paste! {
            store($ref, $val)
        }
    };
}

#[macro_export]
macro_rules! codegen_store_ext {
    ($ref:expr, $val:expr) => {
        paste::paste! {
            store_ext($ref, $val)
        }
    };
}

#[macro_export]
macro_rules! codegen_define_tap_buffer {
    ($name:ident, $size:literal, $reg_group_id:literal) => {
        paste::paste! {
            pub const [< BUFFER_DESC_ $name:upper >] : BufferSpec = BufferSpec {
                name: stringify!($name),
                reg_group_id: Some($reg_group_id),
                size: $size,
                global: false,
            };

            pub const [< REGCOUNT_ $name:upper >] : usize = $size;
            pub const [< REGISTER_GROUP_ $name:upper >] : usize = $reg_group_id;
        }
    };
}

#[macro_export]
macro_rules! codegen_define_global_buffer {
    ($name:ident, $size:literal) => {
        paste::paste! {
            pub const [< BUFFER_DESC_ $name:upper >] : BufferSpec = BufferSpec {
                name: stringify!($name),
                reg_group_id: None,
                size: $size,
                global: true,
            };

            pub const [< REGCOUNT_ $name:upper >] : usize = $size;
        }
    };
}

#[macro_export]
macro_rules! codegen_define_buffer {
    ($name:ident, $size:literal) => {
        paste::paste! {
            pub const [< BUFFER_DESC_ $name:upper >] : BufferSpec = BufferSpec {
                name: stringify!($name),
                reg_group_id: None,
                size: $size,
                global: false,
            };

            pub const [< REGCOUNT_ $name:upper >] : usize = $size;
        }
    };
}

#[macro_export]
macro_rules! codegen_define_buffer_list {
    (
        all: [ $( $name:ident ,)* ],
        rows: [ $( $rows_name:ident ,)* ],
        taps: [ $( $taps_name:ident ,)* ],
        globals: [ $( $globals_name:ident ,)* ],
    ) => {
        paste::paste! {
            pub enum RowBufferId {
                $( [< $name:camel >], )*
                MaxRowBufferId
            }
            pub enum GlobalBufferId {
                $( [< $name:camel >], )*
                MaxGlobalBufferId
            }

            pub const BUFFERS : &'static [$crate::BufferSpec] = &[
                $( [< BUFFER_DESC_ $name:upper >], )*
            ];

            const TAP_GROUP_NAMES : &'static [&'static str] = &[
                $( stringify!($taps_name), )*
            ];

            const ROW_BUF_NAMES : &'static [&'static str] = &[
                $( stringify!($rows_name), )*
            ];

            const GLOBAL_BUF_NAMES : &'static [&'static str] = &[
                $( stringify!($globals_name), )*
            ];


            $(
            pub fn [< get_ $rows_name _buffer >]<T, G, W>(buffers: &Buffers<T, G, W>) -> &T {
                buffers.rows[RowBufferId:: [< $rows_name:camel >] as usize].as_ref().unwrap()
            }
            )*

            $(
            pub fn [< get_ $globals_name _buffer >]<T, G, W>(buffers: &Buffers<T, G, W>) -> &G {
                buffers.globals[GlobalBufferId:: [< $globals_name:camel >] as usize ].as_ref().unwrap()
            }
            )*


            pub fn get_named_buffers<'a, T: Clone>(
                named_buffers: impl IntoIterator<Item=(&'a str, T)>) -> $crate::Buffers<T, T, ()> {
                let mut buffers = Buffers{rows: Vec::new(), globals: Vec::new(), wrapped: ()};
                buffers.rows.resize(RowBufferId::MaxRowBufferId as usize, None);
                buffers.globals.resize(GlobalBufferId::MaxGlobalBufferId as usize, None);

                for (name, buf) in named_buffers {
                    let dest = match name {
                        $(
                            stringify!($rows_name)
                                => &mut buffers.rows[RowBufferId:: [< $rows_name:camel >] as usize],
                        )*
                        $(
                            stringify!($globals_name)
                                => &mut buffers.globals[GlobalBufferId:: [< $globals_name:camel >] as usize],
                        )*
                        _ => panic!("Unknown buffer name {name}")
                    };
                    assert!(dest.is_none(), "Duplicate buffer {name}");
                    *dest = Some(buf);
                }
                buffers
            }
        }
    }
}

#[macro_export]
macro_rules! codegen_bind_layout {
    ($layout:expr, $buffer:expr) => {
        &BoundLayout::new($layout, $buffer)
    };
}

#[macro_export]
macro_rules! codegen_layout_subscript {
    ($layout:expr, $index:expr) => {
        layout_map($layout, |layout| layout[$index])
    };
}

#[macro_export]
macro_rules! codegen_layout_lookup {
    ($layout:expr, $field:ident) => {
        layout_map($layout, |layout| layout.$field)
    };
}

#[macro_export]
macro_rules! codegen_eqz {
    ($value:expr, $loc:literal) => {
        eqz($value).context($loc)?
    };
}
