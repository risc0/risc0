// Copyright 2023 RISC Zero, Inc.
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

use proc_macro2::TokenStream;
use quote::quote_spanned;
use syn::{spanned::Spanned, ItemFn, ReturnType};

pub(super) fn function(input: ItemFn) -> TokenStream {
    let fn_name = &input.sig.ident;
    let inputs = &input.sig.inputs;
    let output = &input.sig.output;

    // Check for function parameters for better spanned error
    if !inputs.is_empty() {
        return quote_spanned! {inputs.span()=>
            compile_error!("The `#[entry]` function should not have parameters");
        };
    }

    // Check for non-unit return type for a better spanned error
    if let ReturnType::Type(_, ty) = output {
        // Allow explicit unit type as return
        if !matches!(**ty, syn::Type::Tuple(ref tuple) if tuple.elems.is_empty()) {
            return quote_spanned! {output.span()=>
                compile_error!("The `#[entry]` function must return `()`");
            };
        }
    }

    let result = quote_spanned! {input.sig.span()=>
        // Type check the given path
        const __ZKVM_ENTRY: fn() = #fn_name;

        // Include generated main in a module so we don't conflict
        // with any other definitions of "main" in this file.
        mod __zkvm_generated_main {
            #[no_mangle]
            fn main() {
                super::__ZKVM_ENTRY()
            }
        }
        #input
    };

    result
}

#[cfg(test)]
mod tests {
    use quote::quote;
    use syn::{parse_quote, ItemFn};

    #[test]
    fn basic_function() {
        let input: ItemFn = parse_quote! {
            #[entry]
            fn foo() {}
        };

        let expected = quote! {
            const __ZKVM_ENTRY: fn() = foo;

            mod __zkvm_generated_main {
                #[no_mangle]
                fn main() {
                    super::__ZKVM_ENTRY()
                }
            }

            #[entry]
            fn foo() {}
        };

        let actual = super::function(input);

        assert_eq!(expected.to_string(), actual.to_string());
    }

    #[test]
    fn basic_function_with_explicit_unit_return() {
        let input: ItemFn = parse_quote! {
            #[entry]
            fn foo() -> () {}
        };

        let expected = quote! {
            const __ZKVM_ENTRY: fn() = foo;

            mod __zkvm_generated_main {
                #[no_mangle]
                fn main() {
                    super::__ZKVM_ENTRY()
                }
            }

            #[entry]
            fn foo() -> () {}
        };

        let actual = super::function(input);

        assert_eq!(expected.to_string(), actual.to_string());
    }

    #[test]
    fn function_with_parameters_should_fail() {
        let input: ItemFn = parse_quote! {
            #[entry]
            fn foo(param: i32) {}
        };

        let actual = super::function(input);

        // Check if the generated code contains the expected compile error
        assert!(actual.to_string().contains("compile_error"),);
        assert!(actual
            .to_string()
            .contains("The `#[entry]` function should not have parameters"),);
    }

    #[test]
    fn function_with_return_should_fail() {
        let input: ItemFn = parse_quote! {
            #[entry]
            fn foo() -> u8 {}
        };

        let actual = super::function(input);

        // Check if the generated code contains the expected compile error
        assert!(actual.to_string().contains("compile_error"),);
        assert!(actual
            .to_string()
            .contains("The `#[entry]` function must return `()`"),);
    }
}
