// Copyright 2025 RISC Zero, Inc.
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

use darling::FromMeta;
use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, ItemFn};

#[derive(Debug, FromMeta)]
#[darling(derive_syn_parse)]
struct Args {
    #[darling(default)]
    skip_if_dev_mode: bool,
}

#[proc_macro_attribute]
pub fn gpu_guard(attr: TokenStream, item: TokenStream) -> TokenStream {
    let args: Args = match syn::parse(attr) {
        Ok(v) => v,
        Err(e) => {
            return e.to_compile_error().into();
        }
    };
    let input = parse_macro_input!(item as ItemFn);

    let attrs = &input.attrs;
    let vis = &input.vis;
    let sig = &input.sig;
    let mut body = input.block.clone();

    let injected = if args.skip_if_dev_mode {
        quote! {
            let __gpu_guard = ::std::primitive::bool::then(
                !::gpu_guard::__is_dev_mode(),
                || ::gpu_guard::acquire_gpu_semaphore().expect("Failed to acquire GPU semaphore")
            );
        }
    } else {
        quote! {
            let __gpu_guard = ::gpu_guard::acquire_gpu_semaphore()
                .expect("Failed to acquire GPU semaphore");
        }
    };

    body.stmts.insert(0, ::syn::parse2(injected).unwrap());

    let result = quote! {
        #(#attrs)*
        #vis #sig #body
    };

    result.into()
}
