#include <iostream>
using namespace std;

long long modPower(long long base, long long power, long long mod) {
    long long result = 1;

    while (power > 0) {
        result = (result * base) % mod;
        power--;
    }

    return result;
}

long long modInverse(long long a, long long mod) {
    for (long long i = 1; i < mod; i++) {
        if ((a * i) % mod == 1)
            return i;
    }
    return -1;
}

int main() {

    long long p = 23;
    long long alpha = 5;
    long long a = 6;

    // Public key
    long long beta = modPower(alpha, a, p);

    // Two messages
    long long M1 = 2;
    long long M2 = 4;

    // Random values
    long long r1 = 3;
    long long r2 = 4;

    // Ciphertext C1
    long long C11 = modPower(alpha, r1, p);
    long long C12 = (M1 * modPower(beta, r1, p)) % p;

    // Ciphertext C2
    long long C21 = modPower(alpha, r2, p);
    long long C22 = (M2 * modPower(beta, r2, p)) % p;

    cout << "C1 = (" << C11 << ", " << C12 << ")" << endl;
    cout << "C2 = (" << C21 << ", " << C22 << ")" << endl;

    // Product Cipher
    long long C1_product = (C11 * C21) % p;
    long long C2_product = (C12 * C22) % p;

    cout << "\nProduct Cipher = ("
         << C1_product << ", "
         << C2_product << ")" << endl;

    // Decryption
    long long K = modPower(C1_product, a, p);
    long long KInverse = modInverse(K, p);

    long long decrypted =
        (C2_product * KInverse) % p;

    cout << "Decrypted Product = "
         << decrypted << endl;

    cout << "M1 * M2 mod p = "
         << (M1 * M2) % p << endl;

    return 0;
}