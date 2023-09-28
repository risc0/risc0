## zkVM Methods

This directory contains the [zkVM] portion of your [Bonsai] application. 
This is where you will define one or more [guest programs] to act as a coprocessor to your [on-chain logic].

> In typical use cases, the only code in this directory that you will need to edit is inside [`guest/src/bin`]. 

### Writing Guest Code
To learn to write code for the zkVM, we recommend [Guest Code 101]. 
Note that you don't need to write host code because the Bonsai Ethereum Relay acts as the zkVM host.

Examples of what you can do in the guest can be found in the [RISC Zero examples].

### From Guest Code to Binary File

Code in the `methods/guest` directory will be compiled into one or more [RISC-V] binaries. 
Build configuration for the methods is included in `methods/build.rs`.

Each will have a corresponding image ID, which is a hash identifying the program.

### Uploading Binary to Bonsai
When [deploying] your application, you will upload your binary to Bonsai where the guest will run when requested.
The image ID will be included in the deployment of the smart contracts to reference your guest program living in Bonsai.

[deploying]: ../deployment-guide
[RISC Zero examples]: https://github.com/risc0/tree/v0.18.0/examples
[Guest Code 101]: https://dev.risczero.com/zkvm/developer-guide/guest-code-101
[on-chain logic]: ../contracts/readme
[`guest/src/bin`]: ./guest/src/bin/
[guest program]: https://dev.risczero.com/terminology#guest-program
[guest programs]: https://dev.risczero.com/terminology#guest-program
[developer documentation]: https://dev.risczero.com
[zkVM]: https://dev.risczero.com/zkvm
[Bonsai]: https://dev.risczero.com/bonsai/
