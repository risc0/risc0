// SPDX-License-Identifier: MIT
pragma solidity ^0.8.26;

contract Contract {
    function isSolved(int256 x) external pure returns (bool) {
        // p(x) = x^4 - 84x^3 + 1765x^2 - 84x + 1764
        return ((x**4)
            - (84 * (x**3))
            + (1765 * (x**2))
            - (84 * x)
            + 1764) == 0;
    }
}
