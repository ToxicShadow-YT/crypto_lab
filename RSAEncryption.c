#include <stdio.h>

// Euclid's algorithm is used to ensure e and phi(n) are relatively prime.
static long long gcd(long long first, long long second) {
    while (second != 0) {
        long long remainder = first % second;
        first = second;
        second = remainder;
    }
    return first;
}

// Repeated squaring calculates base^exponent mod modulus without huge powers.
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

static long long mod_inverse(long long value, long long modulus) {
    long long candidate;
    for (candidate = 1; candidate < modulus; candidate++) {
        if ((candidate * value) % modulus == 1) return candidate;
    }
    return -1;
}

static int is_prime(int value) {
    int divisor;
    if (value < 2) return 0;
    for (divisor = 2; divisor * divisor <= value; divisor++) {
        if (value % divisor == 0) return 0;
    }
    return 1;
}

int main(void) {
    int p, q;
    long long n, phi, e = 2, d, message, ciphertext;

    printf("Enter two different small prime numbers p and q (each <= 10000): ");
    if (scanf("%d%d", &p, &q) != 2 || p > 10000 || q > 10000 ||
            !is_prime(p) || !is_prime(q) || p == q) {
        fprintf(stderr, "p and q must be different primes from 2 through 10000.\n");
        return 1;
    }

    n = (long long)p * q;
    phi = (long long)(p - 1) * (q - 1);
    while (e < phi && gcd(e, phi) != 1) e++;
    if (e >= phi || (d = mod_inverse(e, phi)) < 0) {
        fprintf(stderr, "Could not find RSA key values.\n");
        return 1;
    }

    printf("Public key (e, n): (%lld, %lld)\n", e, n);
    printf("Private key (d, n): (%lld, %lld)\n", d, n);
    printf("Enter a non-negative integer message less than n: ");
    if (scanf("%lld", &message) != 1 || message < 0 || message >= n) {
        fprintf(stderr, "Message must be from 0 through n-1.\n");
        return 1;
    }

    ciphertext = mod_power(message, e, n);
    printf("Ciphertext: %lld\n", ciphertext);
    printf("Decrypted message: %lld\n", mod_power(ciphertext, d, n));
    return 0;
}