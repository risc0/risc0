#include <cstdint>

struct __align__(16) chacha_state {
    uint32_t data[16];
};

// Converts 4 bytes into a single 32-bit word
static uint32_t bytes_to_word(const uint8_t bytes[4])
{
    return (static_cast<uint32_t>(bytes[3]) << 24) |
           (static_cast<uint32_t>(bytes[2]) << 16) |
           (static_cast<uint32_t>(bytes[1]) << 8)  |
            static_cast<uint32_t>(bytes[0]);
}

template<typename T = uint64_t>
static chacha_state initialize_chacha_state(const uint8_t key[32],
                                            const uint8_t nonce[16 - sizeof(T)],
                                            T counter = 0)
{
    assert(sizeof(T) % 4 == 0);

    // Set up the constant values for ChaCha as per specification.
    chacha_state state;
    state.data[0] = 0x61707865;
    state.data[1] = 0x3320646e;
    state.data[2] = 0x79622d32;
    state.data[3] = 0x6b206574;

    // Load the key into the state array.
    for (int i = 0; i < 8; i++) {
        state.data[4 + i] = bytes_to_word(key + 4 * i);
    }

    // Load the counter and nonce into the state array.
    state.data[12] = static_cast<uint32_t>(counter);
    state.data[13] = sizeof(T) > sizeof(uint32_t) ? static_cast<uint32_t>(counter >> 32) : bytes_to_word(nonce);

    int nonce_index = sizeof(T) > sizeof(uint32_t) ? 0 : 4;
    for (int i = 0; i < 2; i++) {
        state.data[14 + i] = bytes_to_word(nonce + nonce_index + 4 * i);
    }

    return state;
}

// Perform a single ChaCha quarter round operation.
static __device__ __forceinline__
void quarter_round(uint32_t& a, uint32_t& b, uint32_t& c, uint32_t& d)
{
    a += b;
    d ^= a;
    d = (d << 16) | (d >> 16);

    c += d;
    b ^= c;
    b = (b << 12) | (b >> 20);

    a += b;
    d ^= a;
    d = (d << 8) | (d >> 24);

    c += d;
    b ^= c;
    b = (b << 7) | (b >> 25);
}

template<int ROUNDS>
static __device__ __forceinline__
void chacha_mix(chacha_state& state, size_t counter)
{
    // Increment counter.
    state.data[12] += (uint32_t)counter;
    if (state.data[12] < (uint32_t)counter) state.data[13]++;
    state.data[13] += (uint32_t)(counter >> 32);

    chacha_state temp_state = state;

    // Perform the ChaCha rounds.
    for (uint32_t round = 0; round < ROUNDS / 2; round++) {
        quarter_round(state.data[0], state.data[4], state.data[8],  state.data[12]);
        quarter_round(state.data[1], state.data[5], state.data[9],  state.data[13]);
        quarter_round(state.data[2], state.data[6], state.data[10], state.data[14]);
        quarter_round(state.data[3], state.data[7], state.data[11], state.data[15]);
        quarter_round(state.data[0], state.data[5], state.data[10], state.data[15]);
        quarter_round(state.data[1], state.data[6], state.data[11], state.data[12]);
        quarter_round(state.data[2], state.data[7], state.data[8],  state.data[13]);
        quarter_round(state.data[3], state.data[4], state.data[9],  state.data[14]);
    }

    // Add the initial state back to the mixed state.
    for (uint32_t j = 0; j < 16; j++) {
        state.data[j] = state.data[j] + temp_state.data[j];
    }
}
