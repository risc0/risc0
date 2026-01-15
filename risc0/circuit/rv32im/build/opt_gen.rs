// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use heck::{ToPascalCase as _, ToShoutySnakeCase as _, ToSnakeCase as _};
use quote::{format_ident, quote};
use risc0_circuit_rv32im_sys::{RV32IM_TABLE, Rv32imInstrInfo};
use std::{
    collections::{BTreeMap, BTreeSet},
    str::FromStr as _,
};

fn param_to_tokens(param: &str) -> syn::Expr {
    let (prefix, rest) = param.split_once("_").unwrap();
    let starts_with_int = u8::from_str(&rest[..1]).is_ok();
    let name = if starts_with_int {
        param.to_pascal_case()
    } else {
        rest.to_pascal_case()
    };

    syn::parse_str(&format!("{}Kind::{name}", prefix.to_pascal_case())).unwrap()
}

fn params_to_tokens(instr: &Rv32imInstrInfo) -> proc_macro2::TokenStream {
    let name = format_ident!("{}", instr.name.to_pascal_case());
    let idx = instr.idx;
    let opcode = instr.opcode;
    let imm_type = format_ident!("{}", instr.imm_type.to_snake_case());
    let func3: syn::Expr = syn::parse_str(instr.func3).unwrap();
    let func7: syn::Expr = syn::parse_str(instr.func7).unwrap();
    let itype_name = format_ident!("{}", instr.itype.to_snake_case());

    let mut params = instr.params.to_vec();
    params.insert(0, instr.itype);
    let params = params.iter().map(|p| param_to_tokens(p));

    quote! {
        (#name, #idx, #opcode, #imm_type, #func3, #func7, #itype_name, #(#params),*)
    }
}

fn instr_option_trait(name: &str, params: &BTreeSet<&str>) -> proc_macro2::TokenStream {
    let name = format_ident!("{}Options", name.to_pascal_case());

    let op_types = params
        .iter()
        .map(|p| format_ident!("{}Kind", p.to_pascal_case()))
        .collect::<Vec<_>>();

    let op_idents = params
        .iter()
        .map(|p| format_ident!("{}_KIND", p.to_shouty_snake_case()))
        .collect::<Vec<_>>();

    quote! {
        #[allow(dead_code)]
        pub trait #name {
            #(const #op_idents: Option<#op_types>;)*

            const OPT_VALUE: u32;
        }
    }
}

fn instr_option_impl(
    entry: &Rv32imInstrInfo,
    trait_name: &str,
    params: &BTreeSet<&str>,
) -> proc_macro2::TokenStream {
    let name = format_ident!("{}Options", entry.name.to_pascal_case());
    let trait_name = format_ident!("{trait_name}");

    let op_types = params
        .iter()
        .map(|p| format_ident!("{}Kind", p.to_pascal_case()))
        .collect::<Vec<_>>();

    let op_idents = params
        .iter()
        .map(|p| format_ident!("{}_KIND", p.to_shouty_snake_case()))
        .collect::<Vec<_>>();

    let mut entry_params = entry.params.to_vec();
    entry_params.insert(0, entry.itype);
    let value_map: BTreeMap<String, _> = entry_params
        .iter()
        .map(|p| {
            let value = param_to_tokens(p);
            let kind = p.split_once("_").unwrap().0.to_string();
            (kind, value)
        })
        .collect();

    let op_values = params.iter().map(|&p| match value_map.get(p) {
        Some(v) => quote!(Some(#v)),
        None => quote!(None),
    });
    let op_values2 = entry_params
        .iter()
        .filter(|&p| params.contains(p.split_once("_").unwrap().0))
        .map(|p| param_to_tokens(p));

    quote! {
        impl #trait_name for #name {
            #(const #op_idents: Option<#op_types> = #op_values;)*

            const OPT_VALUE: u32 = opt![#(#op_values2),*].val();
        }
    }
}

fn generate_options(output: &str, rv32im_table: &[Rv32imInstrInfo]) {
    let names = rv32im_table
        .iter()
        .map(|e| format_ident!("{}", e.name.to_pascal_case()))
        .collect::<Vec<_>>();
    let upper_names = rv32im_table.iter().map(|e| &e.name);
    let entries = rv32im_table.iter().map(params_to_tokens);
    let indexes = rv32im_table.iter().map(|e| e.idx).collect::<Vec<_>>();

    let mut itypes = BTreeMap::new();
    for entry in rv32im_table {
        let e = itypes.entry(entry.itype).or_insert(BTreeSet::new());

        e.insert(entry.itype.split_once("_").unwrap().0);
        for param in entry.params {
            e.insert(param.split_once("_").unwrap().0);
        }
    }

    let mut option_traits = vec![];
    for (itype, params) in &itypes {
        option_traits.push(instr_option_trait(itype, params));
    }

    let mut option_impls = vec![];
    for entry in rv32im_table {
        let trait_name = format!("{}Options", entry.itype.to_pascal_case());
        option_impls.push(instr_option_impl(
            entry,
            &trait_name,
            itypes.get(&entry.itype).unwrap(),
        ));
    }

    let unit_options_params = ["UNIT", "AS", "BIT", "MUL", "DIV", "SHIFT"]
        .into_iter()
        .collect();
    for entry in rv32im_table {
        option_impls.push(instr_option_impl(
            entry,
            "UnitOptions",
            &unit_options_params,
        ));
    }

    let option_structs = rv32im_table.iter().map(|e| {
        let name = format_ident!("{}Options", e.name.to_pascal_case());
        quote!(pub struct #name;)
    });

    let contents = quote! {
        #[repr(u8)]
        #[derive(Copy, Clone, PartialEq, Eq)]
        pub enum Opcode {
            #(#names = #indexes,)*
            Invalid
        }

        impl Opcode {
            pub fn name(&self) -> &'static str {
                match self {
                    #(Self::#names => #upper_names,)*
                    _ => "***UNKNOWN***"
                }
            }
        }

        impl std::fmt::Display for Opcode {
            fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
                self.name().fmt(f)
            }
        }

        impl From<u8> for Opcode {
            fn from(v: u8) -> Self {
                match v {
                    #(#indexes => Self::#names,)*
                    _ => Self::Invalid
                }
            }
        }

        #(#option_structs)*

        #(#option_traits)*

        #(#option_impls)*

        #[macro_export]
        macro_rules! visit_rv32im_instr {
            ($visitor:ident $(, $arg:expr)*) => {
                $visitor!($($arg,)* #(#entries),*)
            }
        }

        pub use visit_rv32im_instr;
    };

    std::fs::write(output, contents.to_string()).unwrap();
    let status = std::process::Command::new("rustfmt")
        .arg(output)
        .status()
        .unwrap();
    assert!(status.success(), "rustfmt {output} failed");
}

pub fn generate(output: &str) {
    generate_options(output, &RV32IM_TABLE[..]);
}
