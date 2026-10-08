#include <stdio.h>
#include <string.h>

static int mod_inverse(int value) {
    int candidate;
    for (candidate = 1; candidate < 26; candidate++) {
        if ((value * candidate) % 26 == 1) return candidate;
    }
    return -1;
}

// A 2x2 key is invertible modulo 26 only if its determinant is coprime to 26.
static int invert_matrix(const int key[2][2], int inverse[2][2]) {
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    int determinant_inverse;
    if (determinant < 0) determinant += 26;
    determinant_inverse = mod_inverse(determinant);
    if (determinant_inverse < 0) return 0;

    inverse[0][0] = (determinant_inverse * key[1][1]) % 26;
    inverse[0][1] = (26 - determinant_inverse * key[0][1] % 26) % 26;
    inverse[1][0] = (26 - determinant_inverse * key[1][0] % 26) % 26;
    inverse[1][1] = (determinant_inverse * key[0][0]) % 26;
    return 1;
}

// Transform text in pairs, treating A=0 through Z=25 and using column vectors.
static void transform(const char *input, char *output, const int matrix[2][2]) {
    size_t i;
    for (i = 0; input[i] != '\0'; i += 2) {
        int x = input[i] - 'A';
        int y = input[i + 1] - 'A';
        output[i] = (char)('A' + (matrix[0][0] * x + matrix[0][1] * y) % 26);
        output[i + 1] = (char)('A' + (matrix[1][0] * x + matrix[1][1] * y) % 26);
    }
    output[i] = '\0';
}

int main(void) {
    char text[258];
    char encrypted[258];
    char decrypted[258];
    int key[2][2];
    int inverse[2][2];
    size_t i;

    printf("Enter plaintext using letters A-Z only: ");
    if (scanf("%257s", text) != 1) return 1;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') text[i] = (char)(text[i] - 'a' + 'A');
        if (text[i] < 'A' || text[i] > 'Z') {
            fprintf(stderr, "Plaintext must contain letters A-Z only.\n");
            return 1;
        }
    }

    printf("Enter the 2x2 key matrix values (0 through 25):\n");
    if (scanf("%d%d%d%d", &key[0][0], &key[0][1], &key[1][0], &key[1][1]) != 4) {
        fprintf(stderr, "Invalid matrix input.\n");
        return 1;
    }
    for (i = 0; i < 2; i++) {
        size_t j;
        for (j = 0; j < 2; j++) {
            if (key[i][j] < 0 || key[i][j] > 25) {
                fprintf(stderr, "Matrix values must be from 0 through 25.\n");
                return 1;
            }
        }
    }
    if (!invert_matrix(key, inverse)) {
        fprintf(stderr, "This matrix is not invertible modulo 26.\n");
        return 1;
    }

    // Add X when needed so the plaintext length is even.
    if (strlen(text) % 2 != 0) strcat(text, "X");
    transform(text, encrypted, key);
    transform(encrypted, decrypted, inverse);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted (including any padding X): %s\n", decrypted);
    return 0;
}