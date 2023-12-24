use proc_macro::TokenStream;

mod entry;

fn token_stream_with_error(mut tokens: TokenStream, error: syn::Error) -> TokenStream {
    tokens.extend(TokenStream::from(error.into_compile_error()));
    tokens
}

/// The `#[entry]` attribute can be used to declare the entry point of a risc0 program.
///
/// # Example
///
/// ```ignore
/// #[risc0_zkvm::entry]
/// fn some_method() {
///     println!("Hello, world!");
/// }
/// ```
#[proc_macro_attribute]
pub fn entry(_attr: TokenStream, item: TokenStream) -> TokenStream {
    // If any of the steps for this macro fail, we still want to expand to an item that is as close
    // to the expected output as possible. This helps out IDEs such that completions and other
    // related features keep working.
    let input: syn::ItemFn = match syn::parse(item.clone()) {
        Ok(it) => it,
        Err(e) => return token_stream_with_error(item, e),
    };

    entry::function(input).into()
}
