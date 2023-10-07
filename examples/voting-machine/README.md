# Voting machine on RISC Zero

A simple voting machine built on the RISC Zero platform.

**This example is for educational purposes only. Not for use in actual elections.**

## Overview

A *voting machine* is a state machine with three operations:

* *Initialize*, which officials use to configure the machine;
* *Submit ballot*, which voters use to submit their ballot;
* *Freeze*, which reveals the current vote count & puts the machine into a state where it no longer accepts ballots.

Every time the voting machine updates its state it prints a "receipt" that
commits it to that state. At the end of the election, officials can publish the
full list of receipts and voters can check to ensure theirs is included. In this
way, voters can confirm that their vote was counted.

## Running the tests

```bash
cargo test --release
```

```console
[2022-03-29T18:13:44Z INFO  test::tests] initial commit: Ok(InitializeVotingMachineCommit { polls_open: true, voter_bitfield: 0, state: c3e42245ffdff31c980d63b232de1414ca2461a08c6efccca2af96737ef4d068 })
[2022-03-29T18:13:44Z INFO  test::tests] ballot 1: Ballot { voter: 0, vote_yes: false }
[2022-03-29T18:13:44Z INFO  test::tests] ballot 1 commit: Ok(SubmitBallotCommit { old_state: c3e42245ffdff31c980d63b232de1414ca2461a08c6efccca2af96737ef4d068, new_state: d05796eb3a889d209cc6e6e6a1429bbd9d218df2b58146a51be1fcafc3164042, polls_open: true, voter_bitfield: 1, voter: 0, vote_counted: true })
[2022-03-29T18:13:44Z INFO  test::tests] ballot 2: Ballot { voter: 1, vote_yes: true }
[2022-03-29T18:13:44Z INFO  test::tests] ballot 2 commit: Ok(SubmitBallotCommit { old_state: d05796eb3a889d209cc6e6e6a1429bbd9d218df2b58146a51be1fcafc3164042, new_state: cf922f404db827ea91f8c423c0621c677b464641fe0b6c6a7aeeb755fa19758b, polls_open: true, voter_bitfield: 3, voter: 1, vote_counted: true })
[2022-03-29T18:13:44Z INFO  test::tests] ballot 3: Ballot { voter: 2, vote_yes: true }
[2022-03-29T18:13:44Z INFO  test::tests] ballot 3 commit: Ok(SubmitBallotCommit { old_state: cf922f404db827ea91f8c423c0621c677b464641fe0b6c6a7aeeb755fa19758b, new_state: 3d5bc2f4e701d3184e5f2874d144b020bbfb3dd4a605509f703d82bd5daad5f2, polls_open: true, voter_bitfield: 7, voter: 2, vote_counted: true })
[2022-03-29T18:13:44Z INFO  test::tests] ballot 4: Ballot { voter: 1, vote_yes: false }
[2022-03-29T18:13:44Z INFO  test::tests] ballot 4 commit: Ok(SubmitBallotCommit { old_state: 3d5bc2f4e701d3184e5f2874d144b020bbfb3dd4a605509f703d82bd5daad5f2, new_state: 3d5bc2f4e701d3184e5f2874d144b020bbfb3dd4a605509f703d82bd5daad5f2, polls_open: true, voter_bitfield: 7, voter: 1, vote_counted: false })
[2022-03-29T18:13:44Z INFO  test::tests] ballot 5: Ballot { voter: 3, vote_yes: false }
[2022-03-29T18:13:44Z INFO  test::tests] ballot 5 commit: Ok(SubmitBallotCommit { old_state: 3d5bc2f4e701d3184e5f2874d144b020bbfb3dd4a605509f703d82bd5daad5f2, new_state: 560897b3110f28db5855b27a713d0bb98300526ced5c5786398d8710e55f5ab7, polls_open: true, voter_bitfield: 15, voter: 3, vote_counted: true })
[2022-03-29T18:13:44Z INFO  test::tests] freeze commit: Ok(FreezeVotingMachineCommit { old_state: 560897b3110f28db5855b27a713d0bb98300526ced5c5786398d8710e55f5ab7, new_state: 9aad1eebf324176d836beec9af1f09812915408082c48895f6271e06943ec116, polls_open: false, voter_bitfield: 15, count: 2 })
[2022-03-29T18:13:44Z INFO  test::tests] ballot 6: Ballot { voter: 4, vote_yes: true }
[2022-03-29T18:13:44Z INFO  test::tests] ballot 6 commit: Ok(SubmitBallotCommit { old_state: 9aad1eebf324176d836beec9af1f09812915408082c48895f6271e06943ec116, new_state: 9aad1eebf324176d836beec9af1f09812915408082c48895f6271e06943ec116, polls_open: false, voter_bitfield: 15, voter: 4, vote_counted: false })
[2022-03-29T18:13:44Z INFO  test::tests] Final vote count: 2
...
```
