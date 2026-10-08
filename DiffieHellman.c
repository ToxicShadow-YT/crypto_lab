#include <stdio.h>

// Repeated squaring calculates modular powers used for public and shared values.
static long long mod_power(long long base, long long exponent, long long modulus) {
    long long result = 1;
    base %= modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent /= 2;
    }
    return result;
}

static int is_prime(int value) {
    int divisor;
    if (value < 2) return 0;
    for (divisor = 2; divisor * divisor <= value; divisor++) {
        if (value % divisor == 0) return 0;
    }
    return 1;
}

// Check that g generates all non-zero residues modulo the small prime p.
static int is_primitive_root(int g, int p) {
    int seen[10000] = {0};
    long long value = 1;
    int count;
    for (count = 0; count < p - 1; count++) {
        value = (value * g) % p;
        if (seen[value]) return 0;
        seen[value] = 1;
    }
    return value == 1;
}

int main(void) {
    int p, g;
    long long alice_private, bob_private;
    long long alice_public, bob_public, alice_key, bob_key;

    printf("Enter a small prime modulus p (5 through 9999): ");
    if (scanf("%d", &p) != 1 || p < 5 || p >= 10000 || !is_prime(p)) {
        fprintf(stderr, "p must be a prime from 5 through 9999.\n");
        return 1;
    }
    printf("Enter primitive root g (2 through p-1): ");
    if (scanf("%d", &g) != 1 || g < 2 || g >= p || !is_primitive_root(g, p)) {
        fprintf(stderr, "g must be a primitive root modulo p.\n");
        return 1;
    }
    printf("Enter Alice's private exponent: ");
    if (scanf("%lld", &alice_private) != 1 || alice_private <= 0) {
        fprintf(stderr, "Private exponent must be positive.\n");
        return 1;
    }
    printf("Enter Bob's private exponent: ");
    if (scanf("%lld", &bob_private) != 1 || bob_private <= 0) {
        fprintf(stderr, "Private exponent must be positive.\n");
        return 1;
    }

    // Each user raises the other user's public value to their own private exponent.
    alice_public = mod_power(g, alice_private, p);
    bob_public = mod_power(g, bob_private, p);
    alice_key = mod_power(bob_public, alice_private, p);
    bob_key = mod_power(alice_public, bob_private, p);
    printf("Alice's public value: %lld\n", alice_public);
    printf("Bob's public value: %lld\n", bob_public);
    printf("Alice's shared key: %lld\n", alice_key);
    printf("Bob's shared key: %lld\n", bob_key);
    printf("Keys match: %s\n", alice_key == bob_key ? "yes" : "no");
    return 0;
}