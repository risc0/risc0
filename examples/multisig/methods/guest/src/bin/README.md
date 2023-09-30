# Guest: Private MultiSig Wallet

### Notes

#### Participant Privacy

You can embed the leaves of the Merkle tree directly within the guest code. 
However, this approach could inadvertently reveal information about the number of participants involved in the multisig, which might not be desirable.
As an alternative, you can pass the leaves to the zkVM code as a parameter. This way, the leaves remain confidential, yet we can still generate the zk proof.

```
    let leaf_one =
    <[u8; 32]>::from_hex("2ded6691f90f8ee99fd9bd72d39b35fd829d8c6654cda03ec709a02674aa334a")
        .expect("Decoding failed");
    let leaf_two =
    <[u8; 32]>::from_hex("e4083e5df4eef0b44a0e9d561ba9bd2ad76a2be3d021b7f2f3725e525352e988")
        .expect("Decoding failed");
    let leaf_three =
    <[u8; 32]>::from_hex("65be2cac622d5019dc04889aec418a2e9c724c456e91e43835b116350a72a42e")
        .expect("Decoding failed");
    let leaf_four =
    <[u8; 32]>::from_hex("1b5810aeb251583acc192df9638a3204798fb95126e91185a39c36728b83eb2c")
        .expect("Decoding failed");
    let leaf_five =
    <[u8; 32]>::from_hex("c5304c10ee245490ee283ebc082cbcfaad838858f4b2e24150c927ff475a2f0b")
        .expect("Decoding failed");
    let leaf_six =
    <[u8; 32]>::from_hex("4b53708aa80dacfc89b939d2944e42a2561515c58a995f255ba80844afb93fd8")
        .expect("Decoding failed");
    let leaves = [
        leaf_one, leaf_two, leaf_three, leaf_four, leaf_five, leaf_six,
    ];
```


#### Replay protection

If we enforce that the 'signedMessage' parameter passed to the zkVM is an Ethereum ERC4337 UserOperation, we would automatically get replay protection. This is because UserOperations require 'nonce' fields to be specified. A smart contract would be responsible for ensuring adherence to replay protection.


##### TODO: Add more information