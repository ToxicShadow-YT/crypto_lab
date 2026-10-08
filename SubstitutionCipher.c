#include <stdio.h>
#include <string.h>

#define ALPHABET "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

static int valid_key(const char *key) {
    int seen[26] = {0};
    int i;

    if (strlen(key) != 26) return 0;
    for (i = 0; i < 26; i++) {
        if (key[i] < 'A' || key[i] > 'Z' || seen[key[i] - 'A']) return 0;
        seen[key[i] - 'A'] = 1;
    }
    return 1;
}

// The key maps plaintext A-Z to ciphertext; inverse lookup decrypts it.
static void transform(const char *input, char *output, const char *key, int decrypt) {
    size_t i;
    for (i = 0; input[i] != '\0'; i++) {
        char ch = input[i];
        char upper = ch;
        int position;
        if (upper >= 'a' && upper <= 'z') upper = (char)(upper - 'a' + 'A');
        position = upper - 'A';

        if (position < 0 || position >= 26) {
            output[i] = ch;
        } else {
            char mapped = decrypt ? (char)('A' + (strchr(key, upper) - key)) : key[position];
            output[i] = (ch >= 'a' && ch <= 'z') ? (char)(mapped - 'A' + 'a') : mapped;
        }
    }
    output[i] = '\0';
}

int main(void) {
    char key[128];
    char text[512];
    char encrypted[512];
    char decrypted[512];

    do {
        printf("Enter a 26-letter key containing every A-Z letter once: ");
        if (scanf("%127s", key) != 1) return 1;
        if (!valid_key(key)) printf("Invalid key. Try again.\n");
    } while (!valid_key(key));
    getchar();

    printf("Enter text: ");
    if (fgets(text, sizeof(text), stdin) == NULL) return 1;
    text[strcspn(text, "\n")] = '\0';

    transform(text, encrypted, key, 0);
    transform(encrypted, decrypted, key, 1);
    printf("Encrypted: %s\n", encrypted);
    printf("Decrypted: %s\n", decrypted);
    return 0;
}