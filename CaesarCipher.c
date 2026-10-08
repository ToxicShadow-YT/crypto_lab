#include <stdio.h>
#include <string.h>

static void transform(const char *input, char *output, int shift) {
    int amount = ((shift % 26) + 26) % 26;
    size_t i;

    for (i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        if (ch >= 'A' && ch <= 'Z') {
            output[i] = (char)('A' + (ch - 'A' + amount) % 26);
        } else if (ch >= 'a' && ch <= 'z') {
            output[i] = (char)('a' + (ch - 'a' + amount) % 26);
        } else {
            output[i] = ch;
        }
    }
    output[i] = '\0';
}

int main(void) {
    char text[512];
    char encrypted[512];
    char decrypted[512];
    int shift;

    printf("Enter text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';

    printf("Enter shift: ");
    if (scanf("%d", &shift) != 1) {
        fprintf(stderr, "Invalid shift.\n");
        return 1;
    }

    transform(text, encrypted, shift);
    transform(encrypted, decrypted, -shift);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    return 0;
}