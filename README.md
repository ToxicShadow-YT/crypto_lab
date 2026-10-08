# Cryptography Lab Programs

These programs are small educational demonstrations. Caesar, substitution, Hill, RSA, and Diffie-Hellman are written in C. RC4 is written in Java as requested. Do not use these textbook implementations for real security.

## 1. Caesar Cipher (C)

**Aim:** Implement Caesar encryption and decryption using a numeric shift.

**Algorithm:** For each English letter, shift its alphabet position by the key modulo 26. Preserve letter case and copy non-letters unchanged. Decrypt by applying the negative shift.

**Formula:** `C = (P + K) mod 26`; `P = (C - K) mod 26`.

**Sample input:** `HELLO`, shift `3`.

**Sample output:**

```text
Encrypted: KHOOR
Decrypted: HELLO
```

**Viva:** What is modulo 26 used for? Why is Caesar easy to break? How are spaces handled?

## 2. Monoalphabetic Substitution Cipher (C)

**Aim:** Encrypt and decrypt text using a permutation of the alphabet.

**Algorithm:** The key is a 26-letter alphabet with no repeated letters. Encryption replaces each plaintext letter with the key letter at the same alphabet position. Decryption finds the ciphertext letter's position in the key and maps back to the normal alphabet.

**Sample key:** `QWERTYUIOPASDFGHJKLZXCVBNM`.

**Sample input:** key above, plaintext `HELLO`.

**Sample output:**

```text
Encrypted: ITSSG
Decrypted: HELLO
```

**Viva:** Why must every key letter be unique? How does decryption reverse the mapping? Why is a monoalphabetic cipher vulnerable to frequency analysis?

## 3. Hill Cipher (2x2, C)

**Aim:** Demonstrate block encryption using matrix multiplication modulo 26.

**Algorithm:** Map A-Z to 0-25 and split plaintext into pairs. Pad an odd-length message with X. Multiply each pair, treated as a column vector, by the 2x2 key modulo 26. Find the modular inverse matrix and apply it to decrypt. The determinant must be relatively prime to 26.

**Formula:** `C = K * P mod 26`; `P = K^-1 * C mod 26`.

**Sample key:** `[[3, 3], [2, 5]]`.

**Sample input:** plaintext `HELP`, then matrix values `3 3 2 5`.

**Sample output:**

```text
Encrypted: HIAT
Decrypted (including any padding X): HELP
```

**Viva:** Why must the determinant have an inverse modulo 26? What does the X padding do? How are letters represented as numbers?

## 4. RSA Encryption (C)

**Aim:** Demonstrate public-key encryption and private-key decryption for a small numeric message.

**Algorithm:** Enter distinct primes p and q. Compute `n = p*q` and `phi = (p-1)*(q-1)`. The program finds e coprime to phi and d as the inverse of e modulo phi. Encrypt with modular exponentiation using e; decrypt with d. For safe arithmetic in this short `long long` demonstration, p and q are limited to 10000.

**Formula:** `C = M^e mod n`; `M = C^d mod n`.

**Sample input:** `p=61`, `q=53`, message `65`.

**Sample output:**

```text
Public key (e, n): (7, 3233)
Private key (d, n): (1783, 3233)
Ciphertext: 2790
Decrypted message: 65
```

**Viva:** What are n and phi(n)? Which key is public? Why must gcd(e, phi) equal 1? Why is real RSA used with padding and much larger keys?

## 5. Diffie-Hellman Key Exchange (C)

**Aim:** Show how two parties derive the same shared value over a public channel.

**Algorithm:** Choose prime p and primitive root g. Alice and Bob each enter a private exponent and calculate public values `g^private mod p`. They exchange public values and raise the received value to their own private exponent modulo p. The program validates that g is a primitive root for the small supplied prime.

**Formula:** `YA = g^XA mod p`; `YB = g^XB mod p`; `K = YB^XA mod p = YA^XB mod p`.

**Sample input:** `p=23`, `g=5`, Alice exponent `6`, Bob exponent `15`.

**Sample output:**

```text
Alice's public value: 8
Bob's public value: 19
Alice's shared key: 2
Bob's shared key: 2
Keys match: yes
```

**Viva:** What values are public and private? Why do both parties get the same key? Does basic Diffie-Hellman authenticate the other party?

## 6. RC4 Stream Cipher (Java)

**Aim:** Implement RC4's key scheduling and pseudo-random generation, then XOR the generated stream with data.

**Algorithm:** KSA initializes and permutes a 256-element state using the key. PRGA updates the state and generates one keystream byte per input byte. XOR encrypts; applying RC4 again with the same key decrypts. Ciphertext is displayed as hexadecimal and converted back to bytes for the demonstration.

**Sample input:** plaintext `Plaintext`, key `Key`.

**Sample output:**

```text
Ciphertext (hex): BBF316E8D940AF0AD3
Decrypted: Plaintext
```

**Viva:** What do KSA and PRGA stand for? Why is XOR reversible with the same keystream? Why should RC4 not be used in modern security?

## Compile and Run

Compile a C program with GCC (or another C compiler):

```text
gcc -std=c11 -Wall -Wextra CaesarCipher.c -o CaesarCipher
```

Run it in Windows PowerShell:

```text
.\CaesarCipher.exe
```

Use the matching source and executable name for the other C programs: `SubstitutionCipher`, `HillCipher`, `RSAEncryption`, and `DiffieHellman`.

Compile and run RC4 with a JDK:

```text
javac RC4Cipher.java
java RC4Cipher
```

The C RSA and Diffie-Hellman examples are intentionally limited to small demo numbers; the classical ciphers and RC4 are insecure and for coursework only.