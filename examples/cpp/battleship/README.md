# Battleship (C++)

'Battleship' is a 2-player hidden information game implemented.

Players produce proofs of game-state and the result of their actions to enable
two players to play fairly with no intermediaries.

The best way to understand how the game works currently is to read the code
and run the tests with debug logging enabled:

```
RISC0_LOG=1 bazelisk run //examples/cpp/battleship:test
```

