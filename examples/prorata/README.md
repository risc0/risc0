# Pro Rata

This example demonstrates how to use the zkVM to calculate pro rata distribution of a dollar amount, and then securely attest to any given recipient that their amount was correctly calculated without disclosing the other payouts. Proof generation includes use of existing Rust crates like `csv` for robust CSV parsing and `rust_decimal` for robust decimal calculations including banker's rounding.

Walking through this example on Linux requires a minimum of around 12GB of RAM and under 20 minutes including compile time on a reasonably modern CPU such as the 8-core Ryzen 5800X.

## Quick Start

First, follow the [examples guide] to install dependencies and check out the correct version of the example.

Then, run the example with:

```bash
cargo run --release
```

[examples guide]: https://dev.risczero.com/api/zkvm/examples/#running-the-examples

## Building

To run tests and then build a copy of the pro rata command line utility:

```
> cargo test --package prorata-cli # about 7 minutes
> cargo build --package prorata-cli --release  # about 7 minutes, can run in parallel with above
> cargo run --package prorata-cli help  # verify binary was built
Usage: host <COMMAND>
...
```

## Usage

### Preparing a CSV file of the allocations

Format the allocations as a CSV with the columns `name` and `share` holding the respective holder's name and quantity of ownership. The share can either be a fraction, such as 0.25 for 25%, or a number of shares, such as 765. It might look something like this cap table from `sample/ingen.csv`:

```csv
name,share
Vanguard Group Inc. (The),48823
Blackrock Inc.,48780
John Hammond,46767
...
Wells Fargo & Company,7572
Northern Trust Corporation,6950
```

### Certifying the input

The first step necessary for trusting an allocation is to know the cap table is correct. After an appropriate audit to make sure the cap table matches the records, an auditor then attests to its correctness. To convince an outside recipient of the authenticity of this attestation our auditors may use `gpg` to sign the statement saying the cap table referenced by hash has passed audit:

```
> date > statement.txt
> echo "We, the auditors, have examined the records and capitalization of InGen Corp. In our opinion the records are adequate and the cap table referenced below is free of material misstatement." >> statement.txt
> shasum -a 256 sample/ingen.csv >> statement.txt
> gpg --no-default-keyring  --keyring sample/auditor.gpg --clear-sign < statement.txt > statement-signed.txt
> cat statement-signed.txt
-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Wed 31 May 2023 05:47:01 PM UTC
We, the auditors, have examined the records and capitalization of InGen Corp. In our opinion the records are adequate and the cap table referenced below is free of material misstatement.
1042f70d38c9e980c14f449714952e04c8aab41967f2ffcafa02cda9ec9dce22  sample/ingen.csv
-----BEGIN PGP SIGNATURE-----

iQGzBAEBCgAdFiEEJUZhvjYoDkDIWTrtZsh2P00awb0FAmR3iC4ACgkQZsh2P00a
...
=Pl0x
-----END PGP SIGNATURE-----
```

Now we have a signed statement from the auditor that we may share with anyone to convince them that our cap table is correct.

### Computing an allocation

Great news! InGen has agreed to be purchased by Masrani Global Corporation and is doing a $1B distribution as part of the sale. Let's calculate how much will go to John Hammond and create a verifiable statement to that effect.

```
> target/release/prorata-cli allocate --input sample/ingen.csv --output hammond.receipt --recipient 'John Hammond' --amount 1000000000
```

### Verifying an allocation

John receives the notice.

```
> cargo run --package prorata-cli verify --input hammond.receipt
Query: John Hammond
Allocation for John Hammond: 187068000
CSV hash: 1042f70d38c9e980c14f449714952e04c8aab41967f2ffcafa02cda9ec9dce22
```

And to check that the cap table is authentic:

```
> gpg --no-default-keyring  --keyring sample/auditor.gpg --verify < statement-signed.txt
gpg: Signature made Wed 31 May 2023 05:47:43 PM UTC
gpg:                using RSA key 254661BE36280E40C8593AED66C8763F4D1AC1BD
gpg: Good signature from "audit@example.com" [unknown]
gpg: WARNING: This key is not certified with a trusted signature!
gpg:          There is no indication that the signature belongs to the owner.
Primary key fingerprint: 2546 61BE 3628 0E40 C859  3AED 66C8 763F 4D1A C1BD
```

Success.
