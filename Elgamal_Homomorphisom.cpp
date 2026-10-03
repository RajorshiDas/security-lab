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

    // Messages
    long long M1 = 2;
    long long M2 = 4;

    // Random values
    long long r1 = 3;
    long long r2 = 4;

    // -------------------------
    // Encrypt M1
    // -------------------------

    long long gamma1 = modPower(alpha, r1, p);

    long long delta1 =
        (M1 * modPower(beta, r1, p)) % p;

    // C1 = (gamma1, delta1)
    cout << "C1 = (" << gamma1 << ", "
         << delta1 << ")" << endl;


    // -------------------------
    // Encrypt M2
    // -------------------------

    long long gamma2 = modPower(alpha, r2, p);

    long long delta2 =
        (M2 * modPower(beta, r2, p)) % p;

    // C2 = (gamma2, delta2)
    cout << "C2 = (" << gamma2 << ", "
         << delta2 << ")" << endl;


    // -------------------------
    // Homomorphic multiplication
    // -------------------------

    long long gamma =
        (gamma1 * gamma2) % p;

    long long delta =
        (delta1 * delta2) % p;

    cout << "\nC1 * C2 = ("
         << gamma << ", "
         << delta << ")" << endl;


    // -------------------------
    // Decrypt combined ciphertext
    // -------------------------

    long long K = modPower(gamma, a, p);

    long long KInverse = modInverse(K, p);

    long long decrypted =
        (delta * KInverse) % p;

    cout << "Decrypted result = "
         << decrypted << endl;


    // Expected result
    long long expected =
        (M1 * M2) % p;

    cout << "M1 * M2 mod p = "
         << expected << endl;

    return 0;
}