# Mock of the Bonsai REST API

An HTTP REST API server to mock the Bonsai-alpha prover interface.
The service provides execution only, no proving. It can be configured to run on a given port.

## Example Usage

```rust
#[tokio::main]
async fn main() {
    let _ = bonsai_local_api_mock::serve("8081".to_string()).await;
}
```