// Copyright 2022 RISC Zero, Inc.
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

// DO NOT MERGE: Test copyright script

use proc_macro2::TokenStream;
use quote::{format_ident, quote, ToTokens};
use syn::{
    parse_macro_input, punctuated::Punctuated, spanned::Spanned, token::Comma, DataEnum,
    DataStruct, DeriveInput, Error, Fields, GenericParam, Generics, Ident, Index, Lifetime,
    LifetimeDef, Result, Variant, Visibility,
};

#[derive(Default, Debug)]
struct GenericFragments {
    // Results from syn's split_for_impl()
    impl_generics: TokenStream,
    ty_generics: TokenStream,
    where_clause: TokenStream,

    // Generated name for the "reference" type.
    ref_name: TokenStream,

    // Same, but for the generated reference type.
    ref_impl_generics: TokenStream,
    ref_ty_generics: TokenStream,
    //    ref_ty_generics_turbofish: TokenStream,
    ref_where_clause: TokenStream,

    phantom_types: TokenStream,
}

fn to_tokens<T: ToTokens>(t: &T) -> TokenStream {
    let mut tokens = TokenStream::new();
    t.to_tokens(&mut tokens);
    tokens
}

fn warning_inhibit() -> TokenStream {
    quote! {
        #[allow(unused_parens, non_camel_case_types, unused_variables, dead_code, missing_docs)]
    }
}

fn make_generics(ref_name: &Ident, generics: &Generics) -> GenericFragments {
    let (impl_generics, ty_generics, where_clause) = generics.split_for_impl();

    // We need this parameterized with a 'zeroio_deserialize' lifetime so that
    // the reference structure outlives the buffer it points to.
    let mut ref_generics = generics.clone();
    let zeroio_lifetime = GenericParam::Lifetime(LifetimeDef::new(Lifetime::new(
        "'zeroio_deserialize",
        generics.span().unwrap().into(),
    )));
    ref_generics.params.push(zeroio_lifetime);
    let (ref_impl_generics, ref_ty_generics, ref_where_clause) = ref_generics.split_for_impl();
    //    let ref_ty_generics_turbofish = ref_ty_generics.as_turbofish();

    // Since we don't actually hold any of the parameterized types, we
    // have to reference them using PhantomData.
    let mut phantom_types = Punctuated::<TokenStream, Comma>::from_iter(
        generics.params.iter().filter_map(|p| match p {
            GenericParam::Type(p) => Some(to_tokens(&p.ident)),
            _ => None,
        }),
    );
    phantom_types.push(quote! {&'zeroio_deserialize ()});

    GenericFragments {
        impl_generics: to_tokens(&impl_generics),
        ty_generics: to_tokens(&ty_generics),
        where_clause: to_tokens(&where_clause),
        ref_name: to_tokens(&ref_name),
        ref_impl_generics: to_tokens(&ref_impl_generics),
        ref_ty_generics: to_tokens(&ref_ty_generics),
        //        ref_ty_generics_turbofish: to_tokens(&ref_ty_generics_turbofish),
        ref_where_clause: to_tokens(&ref_where_clause),
        phantom_types: to_tokens(&phantom_types),
    }
}

// Fragments for generating structures.
#[derive(Debug)]
struct StructFragments {
    field_name: Vec<Ident>,

    // Length calculation expressions
    fixed_words: TokenStream,
    tot_len: TokenStream,

    // "fill" implementation (for Serialize)
    fill: TokenStream,

    // For named structures, implementations of accessor methods.
    accessors: TokenStream,

    // Body of the implementation of Deserialize.
    deserialize_impl: TokenStream,

    // If this is a tuple, generated names for the fields if we have to store them in variables.
    tuple_id: Vec<TokenStream>,

    // Create reference types
    declare_ref: TokenStream,

    // Convert from reference to original
    from_ref: TokenStream,
}

// Returns fragments for building serializable and deserializable
// structures.  We can compose these to either generate a named struct
// or an enum struct variant.
fn make_struct_impls(
    selfname: &TokenStream,
    vis: &Visibility,
    fields: &Fields,
    generics: &GenericFragments,
    is_enum: bool,
) -> StructFragments {
    // Names and types of struct fields.
    let field_name: Vec<Ident> = fields.iter().flat_map(|f| &f.ident).cloned().collect();
    let field_ty: Vec<TokenStream> = fields.iter().map(|f| to_tokens(&f.ty)).collect();

    // Names for tuple parts when accessing locally in a member function.
    let tuple_id: Vec<_> = (0..fields.len())
        .map(|idx| match is_enum {
            true => to_tokens(&format_ident!("elem{idx}")),
            false => {
                // We want self.0, not self.0usize
                let idx = Index::from(idx);
                quote! { self . #idx }
            }
        })
        .collect();

    // Calculate starting offsets in the structure based off the fixed
    // length of each field.
    let field_offsets: Vec<_> = (0..field_ty.len())
        .map(|idx| {
            if idx == 0 {
                quote! { 0 }
            } else {
                let part_ty = &field_ty[0..idx];
                quote! {
                    #( <#part_ty as risc0_zeroio::Deserialize<'_>> :: FIXED_WORDS)+*
                }
            }
        })
        .collect();

    let fixed_words = match &fields {
        Fields::Unit => quote! {0},
        Fields::Named(_) | Fields::Unnamed(_) => quote! {
            #(<#field_ty as risc0_zeroio::Serialize>::FIXED_WORDS)+*
        },
    };
    let selfref = if is_enum {
        quote! {}
    } else {
        quote! {self.}
    };
    let tot_len = match &fields {
        Fields::Unit => quote! {0},
        Fields::Named(_) => quote! {
            #(#selfref #field_name . tot_len())+*
        },
        Fields::Unnamed(_) => quote! {
            #(#tuple_id . tot_len())+*
        },
    };

    let fill = match &fields {
        Fields::Unit => {
            quote! { Ok(()) }
        }
        Fields::Named(_) => {
            quote! {
                let pos: usize = 0;
                #(
                    #selfref #field_name . fill(&mut _buf.descend(
                        pos, <#field_ty as risc0_zeroio::Serialize>::FIXED_WORDS)?, _a)?;
                    let pos = pos + <#field_ty as risc0_zeroio::Serialize>::FIXED_WORDS;
                )*

                Ok(())
            }
        }
        Fields::Unnamed(_) => {
            quote! {
                let pos: usize = 0;
                #(
                    #tuple_id . fill(&mut _buf.descend(
                        pos, <#field_ty as risc0_zeroio::Serialize>::FIXED_WORDS)?, _a)?;
                    let pos = pos + <#field_ty as risc0_zeroio::Serialize>::FIXED_WORDS;
                )*

                Ok(())
            }
        }
    };

    // Field accessors
    let accessors = match &fields {
        Fields::Unit => TokenStream::new(),
        Fields::Named(_) => quote! {
            // For each field, generate an accessor method.
            #(
                #vis fn #field_name(&self) ->
                    <#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::RefType {
                        <#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::deserialize_from(
                            &self.buf[#field_offsets ..]
                        )
                    }
            )*
        },
        Fields::Unnamed(_) => {
            let tuple_method = (0..fields.len()).map(|idx| format_ident!("elem{}", idx));

            quote! {#(
                #vis fn #tuple_method(&self) -> <#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::RefType {
                    <#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::deserialize_from(
                        &self.buf[#field_offsets ..]
                    )
                }
            )*}
        }
    };

    let from_ref = match &fields {
        Fields::Unit => {
            quote! { #selfname }
        }
        Fields::Named(_) => quote! {
            #selfname{#(
                #field_name:
                <#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::from_ref(
                    &<#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::deserialize_from(&_val.buf[#field_offsets ..]))
            ),*}
        },
        Fields::Unnamed(_) => quote! {
        #selfname(#(
            <#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::from_ref(
                &<#field_ty as risc0_zeroio::Deserialize<'zeroio_deserialize>>::deserialize_from(&_val.buf[#field_offsets ..]))
        ),*)},
    };

    let GenericFragments {
        ref_name,
        ref_ty_generics,
        phantom_types,
        ..
    } = generics;

    let inhibit_warns = warning_inhibit();
    let declare_ref = quote! {
        #inhibit_warns
        #vis struct #ref_name #ref_ty_generics {
            buf: &'zeroio_deserialize [u32],
            phantom: core::marker::PhantomData <(#phantom_types)>,
        }
    };

    let deserialize_impl = match &fields {
        Fields::Unit => quote! {

            type RefType = #ref_name #ref_ty_generics;

            const FIXED_WORDS : usize = 0;

            fn deserialize_from(_buf: &'zeroio_deserialize [u32]) -> Self::RefType {
                Self::RefType{phantom: core::marker::PhantomData}
            }

            fn from_ref(_val: &Self::RefType) -> Self {
                #from_ref
            }
        },
        Fields::Named(_) | Fields::Unnamed(_) => quote! {
            type RefType = #ref_name #ref_ty_generics;

            const FIXED_WORDS : usize =
                #(<#field_ty as risc0_zeroio::Deserialize<'_>>::FIXED_WORDS)+* ;

            fn deserialize_from(_buf: &'zeroio_deserialize [u32]) -> Self::RefType {
                Self::RefType { buf: _buf, phantom: core::marker::PhantomData }
            }

            fn from_ref(_val: &Self::RefType) -> Self {
                #from_ref
            }
        },
    };

    StructFragments {
        tot_len,
        fill,
        declare_ref,
        deserialize_impl,
        tuple_id,
        accessors,
        fixed_words,
        field_name,
        from_ref,
    }
}

fn emit_serialize_struct(input: &DeriveInput, st: &DataStruct) -> Result<TokenStream> {
    // Name of this structure
    let name = &input.ident;

    let genfrags @ GenericFragments {
        impl_generics,
        ty_generics,
        where_clause,
        ..
    } = &make_generics(&format_ident!("{}Ref", name), &input.generics);

    let StructFragments {
        fixed_words,
        tot_len,
        fill,
        ..
    } = make_struct_impls(&quote! {#name}, &input.vis, &st.fields, &genfrags, false);

    // We serialize structures as simply all the fields in order.
    let inhibit_warns = warning_inhibit();
    let expanded = quote! {
        #inhibit_warns
        impl #impl_generics risc0_zeroio::Serialize for #name #ty_generics #where_clause {
            const FIXED_WORDS : usize = #fixed_words;

            fn tot_len(&self) -> usize { #tot_len }

            fn fill(&self, _buf: & mut risc0_zeroio::AllocBuf,
                    _a: &mut risc0_zeroio::Alloc) -> risc0_zeroio::Result<()> {
                #fill
            }
        }
    };

    Ok(expanded.into())
}

fn emit_deserialize_struct(input: &DeriveInput, fields: &Fields) -> Result<TokenStream> {
    // Name of this structure
    let name = &input.ident;

    let genfrags @ GenericFragments {
        ty_generics,
        where_clause,
        ref_name,
        ref_impl_generics,
        ref_ty_generics,
        ref_where_clause,
        ..
    } = &make_generics(&format_ident!("{}Ref", name), &input.generics);

    let StructFragments {
        accessors,
        declare_ref,
        deserialize_impl,
        ..
    } = make_struct_impls(&quote! {#name}, &input.vis, fields, &genfrags, false);

    let inhibit_warns = warning_inhibit();
    let vis = &input.vis;
    let expanded = quote! {
        #declare_ref

        #inhibit_warns
        impl #ref_impl_generics #ref_name #ref_ty_generics #ref_where_clause {
            #accessors

            #vis fn into_orig(&self) -> #name #ty_generics {
                <#name #ty_generics as risc0_zeroio::Deserialize<'zeroio_deserialize>>::from_ref(&self)
            }
        }

        // Deserialize trait; construct this from a buffer.
        #inhibit_warns
        impl #ref_impl_generics risc0_zeroio::Deserialize<'zeroio_deserialize> for #name #ty_generics #where_clause {
            #deserialize_impl
        }
    };

    Ok(expanded.into())
}

fn make_var_generated_type(name: &Ident, var_name: &Ident) -> Ident {
    format_ident!("{}Ref", format!("{}::{}", name, var_name).replace(":", "_"))
}

// Fragments for each variant
struct VarFragments {
    var: Variant,

    var_id: usize,
    var_name: Ident,
    // Generated types
    var_ref_ty: Ident,

    st: StructFragments,
}

fn make_var_frags(name: &Ident, vis: &Visibility, var: &Variant, var_id: usize) -> VarFragments {
    let var_name = var.ident.clone();
    let var_ref_ty = make_var_generated_type(name, &var_name);
    let generics = make_generics(&var_ref_ty, &Generics::default());
    let st = make_struct_impls(
        &quote! {#name :: #var_name},
        vis,
        &var.fields,
        &generics,
        true,
    );
    VarFragments {
        var: var.clone(),
        var_id,
        var_name,
        var_ref_ty,
        st,
    }
}

fn make_enum_frags(name: &Ident, vis: &Visibility, en: &DataEnum) -> Vec<VarFragments> {
    en.variants
        .iter()
        .enumerate()
        .map(|(var_id, var)| make_var_frags(name, vis, var, var_id))
        .collect()
}

fn emit_serialize_enum(input: &DeriveInput, en: &DataEnum) -> Result<TokenStream> {
    // Name of this enum
    let name = &input.ident;

    let GenericFragments {
        impl_generics,
        ty_generics,
        where_clause,
        ..
    } = make_generics(&format_ident!("{}Ref", name), &input.generics);

    let vars = make_enum_frags(name, &input.vis, en);

    let match_tot_len = vars.iter().map(
        |VarFragments {
             var,
             var_name,
             st:
                 StructFragments {
                     tot_len,
                     field_name,
                     tuple_id,
                     ..
                 },
             ..
         }| {
            match var.fields {
                Fields::Unit => quote! {
                    #name :: #var_name => #tot_len
                },
                Fields::Named(_) => quote! {
                    #name :: #var_name{ #(#field_name),* } => #tot_len
                },
                Fields::Unnamed(_) => quote! {
                    #name :: #var_name( #(#tuple_id),* ) => #tot_len
                },
            }
        },
    );

    let match_and_fill = vars.iter().map(
        |VarFragments {
             var,
             var_id,
             var_name,
             st:
                 StructFragments {
                     fill,
                     field_name,
                     tuple_id,
                     fixed_words,
                     ..
                 },
             ..
         }| {
            let var_id = *var_id as u32;
            let enumfill = quote! {
                let mut vardata = _a.alloc(#fixed_words)?;
                {
                    let _buf = &mut vardata;
                    #fill
                }?;
                _enumbuf.fill_from([#var_id, vardata.rel_ptr_from(_enumbuf)])
            };
            match var.fields {
                Fields::Unit => quote! {
                    #name :: #var_name => { #enumfill }
                },
                Fields::Named(_) => quote! {
                    #name :: #var_name{ #(#field_name),* } => { #enumfill }
                },
                Fields::Unnamed(_) => quote! {
                    #name :: #var_name( #(#tuple_id).* ) => { #enumfill }
                },
            }
        },
    );

    // We serialize enums as a descriminant ID, and a pointer to the variant inside.
    let inhibit_warns = warning_inhibit();
    let expanded = quote! {
        #inhibit_warns
        impl #impl_generics risc0_zeroio::Serialize for #name #ty_generics #where_clause {
            // One word for id, one word for pointer.
            const FIXED_WORDS: usize = 2;

            fn tot_len(&self) -> usize {
                <Self as risc0_zeroio::Serialize>::FIXED_WORDS + match self {
                    #(#match_tot_len,)*
                }
            }

            fn fill(&self, _enumbuf: &mut risc0_zeroio::AllocBuf, _a: &mut risc0_zeroio::Alloc)
                    -> risc0_zeroio::Result<()> {
                match self {
                    #(#match_and_fill,)*
                }
            }
        }
    };
    Ok(expanded.into())
}

fn emit_deserialize_enum(input: &DeriveInput, en: &DataEnum) -> Result<TokenStream> {
    // Name of this enum
    let name = &input.ident;
    let vis = &input.vis;

    let GenericFragments {
        ty_generics,
        where_clause,
        ref_name,
        ref_impl_generics,
        ref_ty_generics,
        ..
    } = &make_generics(&format_ident!("{}Ref", name), &input.generics);

    let vars = &make_enum_frags(name, &input.vis, en);

    let var_name: &Vec<_> = &vars.iter().map(|var| &var.var_name).collect();
    let var_ref_ty = vars.iter().map(|var| &var.var_ref_ty);

    let declare_ref = vars.iter().map(|var| &var.st.declare_ref);

    let match_and_deser = vars.iter().map(
        |VarFragments {
             var_id,
             var_name,
             var_ref_ty,
             ..
         }| {
            let var_id = *var_id as u32;
            quote! {
                #var_id => Self::RefType::#var_name(
                    #var_ref_ty::<'zeroio_deserialize>::deserialize_from(&_buf[ptr as usize..]))
            }
        },
    );

    let ref_impl = vars.iter().map(
        |VarFragments {
             var_ref_ty,
             st:
                 StructFragments {
                     accessors,
                     from_ref,
                     ..
                 },
             ..
         }| {
            quote! {
                impl<'zeroio_deserialize> #var_ref_ty <'zeroio_deserialize> {
                    #accessors

                    fn deserialize_from(_buf: &'zeroio_deserialize [u32]) -> Self {
                        Self{buf: _buf, phantom: core::marker::PhantomData}
                    }

                    pub fn into_orig(&self) -> #name {
                        let _val = self;
                        #from_ref
                    }
                }
            }
        },
    );

    let inhibit_warns = warning_inhibit();
    let expanded = quote! {
        #inhibit_warns
        #vis enum #ref_name #ref_ty_generics {#(
                #var_name(#var_ref_ty<'zeroio_deserialize>),
        )*}

        // Constructed reference types for each variant
        #(#declare_ref)*
        #(#ref_impl)*

        // Deserialize trait; construct this from a buffer.
        #inhibit_warns
        impl #ref_impl_generics risc0_zeroio::Deserialize<'zeroio_deserialize> for #name #ty_generics #where_clause {
            type RefType = #ref_name #ref_ty_generics;

            const FIXED_WORDS : usize = 2;

            fn deserialize_from(_buf: &'zeroio_deserialize [u32]) -> Self::RefType {
                let (id, ptr) = (_buf[0], _buf[1]);
                match id {
                    #(#match_and_deser,)*
                    _ => panic!("Unknown variant id {}", id)
                }
            }

            fn from_ref(_val: &Self::RefType) -> Self {
                match _val {#(
                    Self::RefType::#var_name(ref var) => var.into_orig()
                ,)*}
            }
        }
    };

    Ok(expanded.into())
}

// With the debug-derive feature, this dumps out all the generated
// code and the includes it via include! so we can see errors in
// context.
fn debug_dump(ty: &str, ident: &Ident, res: &mut TokenStream) {
    if cfg!(feature = "debug-derive") {
        let filename = format!("{ty}-{ident}.rs");
        let manifest_dir = std::env::var("CARGO_MANIFEST_DIR").unwrap();
        let path = std::path::Path::new(&manifest_dir)
            .join("src")
            .join(&filename);
        std::fs::write(&path, format!("{}", res)).unwrap();

        let pathname = path.display().to_string();
        *res = quote! {
            include!(#pathname);
        };
    }
}

#[proc_macro_derive(Serialize)]
pub fn derive_serialize(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    let input = parse_macro_input!(input as DeriveInput);

    let mut res = match &input.data {
        syn::Data::Struct(ref st) => emit_serialize_struct(&input, st),
        syn::Data::Enum(en) => emit_serialize_enum(&input, &en),
        _ => Err(Error::new(
            input.span().unwrap().into(),
            "Zeroio derive only supports structs and enums",
        )),
    }
    .unwrap_or_else(|err| Error::to_compile_error(&err).into());
    debug_dump("ser", &input.ident, &mut res);
    res.into()
}

#[proc_macro_derive(Deserialize)]
pub fn derive_deserialize(input: proc_macro::TokenStream) -> proc_macro::TokenStream {
    let input = parse_macro_input!(input as DeriveInput);

    let mut res = match &input.data {
        syn::Data::Struct(st) => emit_deserialize_struct(&input, &st.fields),
        syn::Data::Enum(en) => emit_deserialize_enum(&input, &en),
        _ => Err(Error::new(
            input.span().unwrap().into(),
            "Zeroio derive only supports structs and enums",
        )),
    }
    .unwrap_or_else(|err| Error::to_compile_error(&err).into());
    debug_dump("deser", &input.ident, &mut res);
    res.into()
}
