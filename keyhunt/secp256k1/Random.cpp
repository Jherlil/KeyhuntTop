/*
 * xoshiro256** random number generator implementation
 * Replaces Mersenne Twister for higher performance
 */

#include "Random.h"
#include <stdint.h>

#if defined(_WIN64) && !defined(__CYGWIN__)
// Windows fallback will not use getrandom
#else
#include <sys/random.h>
#endif

// xoshiro256** state
static uint64_t s[4];

static inline uint64_t rotl(const uint64_t x, int k) {
    return (x << k) | (x >> (64 - k));
}

static uint64_t splitmix64(uint64_t *seed) {
    uint64_t z = (*seed += 0x9e3779b97f4a7c15ULL);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
    return z ^ (z >> 31);
}

static inline uint64_t next(void) {
    const uint64_t result = rotl(s[1] * 5ULL, 7) * 9ULL;

    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;
    s[3] = rotl(s[3], 45);

    return result;
}

// seed the generator
void rseed(unsigned long seed) {
    uint64_t x = seed;
    for (int i = 0; i < 4; ++i) {
        s[i] = splitmix64(&x);
    }
}

#if defined(_WIN64) && !defined(__CYGWIN__)
unsigned long rndl() {
    return (unsigned long)next();
}
#else
unsigned long rndl() {
    unsigned long r;
    int bytes_read = getrandom(&r, sizeof(unsigned long), GRND_NONBLOCK);
    if (bytes_read > 0) {
        return r;
    }
    return (unsigned long)next();
}
#endif

// Returns a uniform distributed double value in the interval ]0,1[
double rnd() {
    const uint64_t x = next();
    return (x >> 11) * (1.0 / 9007199254740992.0); // 2^53
}
