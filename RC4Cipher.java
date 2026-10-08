import java.nio.charset.StandardCharsets;
import java.util.Scanner;

public class RC4Cipher {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter plaintext: ");
        byte[] plaintext = scanner.nextLine().getBytes(StandardCharsets.UTF_8);
        System.out.print("Enter a non-empty key: ");
        byte[] key = scanner.nextLine().getBytes(StandardCharsets.UTF_8);
        if (key.length == 0) {
            System.out.println("Key must not be empty.");
            return;
        }

        byte[] ciphertext = applyRc4(plaintext, key);
        System.out.println("Ciphertext (hex): " + toHex(ciphertext));

        // Convert the displayed hex back to bytes before demonstrating decryption.
        byte[] ciphertextBytes = fromHex(toHex(ciphertext));
        byte[] decrypted = applyRc4(ciphertextBytes, key);
        System.out.println("Decrypted: " + new String(decrypted, StandardCharsets.UTF_8));
    }

    // KSA initializes and permutes the 256-byte state using the user key.
    private static int[] keySchedule(byte[] key) {
        int[] state = new int[256];
        for (int i = 0; i < 256; i++) state[i] = i;

        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + state[i] + (key[i % key.length] & 0xFF)) & 0xFF;
            swap(state, i, j);
        }
        return state;
    }

    // PRGA generates a keystream byte for each input byte; XOR performs encryption/decryption.
    private static byte[] applyRc4(byte[] input, byte[] key) {
        int[] state = keySchedule(key);
        byte[] output = new byte[input.length];
        int i = 0;
        int j = 0;
        for (int position = 0; position < input.length; position++) {
            i = (i + 1) & 0xFF;
            j = (j + state[i]) & 0xFF;
            swap(state, i, j);
            int streamByte = state[(state[i] + state[j]) & 0xFF];
            output[position] = (byte) (input[position] ^ streamByte);
        }
        return output;
    }

    private static void swap(int[] state, int first, int second) {
        int temporary = state[first];
        state[first] = state[second];
        state[second] = temporary;
    }

    private static String toHex(byte[] bytes) {
        StringBuilder hex = new StringBuilder(bytes.length * 2);
        for (byte value : bytes) hex.append(String.format("%02X", value & 0xFF));
        return hex.toString();
    }

    private static byte[] fromHex(String hex) {
        byte[] bytes = new byte[hex.length() / 2];
        for (int i = 0; i < bytes.length; i++) {
            int high = Character.digit(hex.charAt(i * 2), 16);
            int low = Character.digit(hex.charAt(i * 2 + 1), 16);
            bytes[i] = (byte) ((high << 4) + low);
        }
        return bytes;
    }
}