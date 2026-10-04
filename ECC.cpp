#include<bits/stdc++.h>
using namespace std;

const int P = 17;
const int A = 2;

struct Point
{
    int x, y;
};

int mod(int a)
{
    return (a % P + P) % P;
}

int modInverse(int a)
{
    for(int i = 1; i < P; i++)
    {
        if(mod(a * i) == 1)
        {
            return i;
        }
    }
    return -1;
}

Point add(Point P1, Point P2)
{
    int s;

    // Point doubling
    if(P1.x == P2.x && P1.y == P2.y)
    {
        int numerator = mod(3 * P1.x * P1.x + A);
        int denominator = mod(2 * P1.y);

        int inverse = modInverse(denominator);

        s = mod(numerator * inverse);
    }
    // Point addition
    else
    {
        int numerator = mod(P2.y - P1.y);
        int denominator = mod(P2.x - P1.x);

        int inverse = modInverse(denominator);

        s = mod(numerator * inverse);
    }

    Point r;

    r.x = mod(s * s - P1.x - P2.x);

    r.y = mod(s * (P1.x - r.x) - P1.y);

    return r;
}

Point multiply(Point P1, int k)
{
    Point r = P1;

    for(int i = 1; i < k; i++)
    {
        r = add(r, P1);
    }

    return r;
}

void printPoint(Point P)
{
    cout << "(" << P.x << ", " << P.y << ")";
}

int main()
{
    // ==========================================
    // ECC PARAMETERS
    // Curve: y^2 = x^3 + 2x + 2 mod 17
    // ==========================================

    Point G = {5, 1};

    // Private key
    int d = 2;

    // Public key Q = dG
    Point Q = multiply(G, d);

    cout << "Private key: " << d << endl;

    cout << "Base point G: ";
    printPoint(G);
    cout << endl;

    cout << "Public key Q = dG: ";
    printPoint(Q);
    cout << endl;


    // ==========================================
    // ECC ELGAMAL ENCRYPTION
    // ==========================================

    // Message point
    Point M = {6, 3};

    // Random value
    int k = 3;

    // C1 = kG
    Point C1 = multiply(G, k);

    // kQ
    Point kQ = multiply(Q, k);

    // C2 = M + kQ
    Point C2 = add(M, kQ);

    cout << "\n----- ECC ELGAMAL ENCRYPTION -----" << endl;

    cout << "Message M: ";
    printPoint(M);
    cout << endl;

    cout << "Random value k: " << k << endl;

    cout << "C1 = kG: ";
    printPoint(C1);
    cout << endl;

    cout << "kQ: ";
    printPoint(kQ);
    cout << endl;

    cout << "C2 = M + kQ: ";
    printPoint(C2);
    cout << endl;

    cout << "Ciphertext: ";
    printPoint(C1);
    cout << " , ";
    printPoint(C2);
    cout << endl;


    // ==========================================
    // ECC ELGAMAL DECRYPTION
    // ==========================================

    // dC1
    Point dC1 = multiply(C1, d);

    // Negative of dC1
    Point negative_dC1 =
    {
        dC1.x,
        mod(-dC1.y)
    };

    // M = C2 - dC1
    Point decryptedM = add(C2, negative_dC1);

    cout << "\n----- ECC ELGAMAL DECRYPTION -----" << endl;

    cout << "dC1: ";
    printPoint(dC1);
    cout << endl;

    cout << "-dC1: ";
    printPoint(negative_dC1);
    cout << endl;

    cout << "Decrypted message: ";
    printPoint(decryptedM);
    cout << endl;


    // ==========================================
    // ECC HOMOMORPHIC ADDITION
    // ==========================================

    Point M1 = {6, 3};
    Point M2 = {5, 1};

    // IMPORTANT:
    // These values avoid the point-at-infinity problem.
    int k1 = 1;
    int k2 = 1;


    // ------------------------------------------
    // Encrypt M1
    // ------------------------------------------

    Point k1G = multiply(G, k1);
    Point k1Q = multiply(Q, k1);

    Point C11 = k1G;
    Point C12 = add(M1, k1Q);

    cout << "\n----- ENCRYPTION OF M1 -----" << endl;

    cout << "M1: ";
    printPoint(M1);
    cout << endl;

    cout << "k1: " << k1 << endl;

    cout << "C11 = k1G: ";
    printPoint(C11);
    cout << endl;

    cout << "C12 = M1 + k1Q: ";
    printPoint(C12);
    cout << endl;


    // ------------------------------------------
    // Encrypt M2
    // ------------------------------------------

    Point k2G = multiply(G, k2);
    Point k2Q = multiply(Q, k2);

    Point C21 = k2G;
    Point C22 = add(M2, k2Q);

    cout << "\n----- ENCRYPTION OF M2 -----" << endl;

    cout << "M2: ";
    printPoint(M2);
    cout << endl;

    cout << "k2: " << k2 << endl;

    cout << "C21 = k2G: ";
    printPoint(C21);
    cout << endl;

    cout << "C22 = M2 + k2Q: ";
    printPoint(C22);
    cout << endl;


    // ==========================================
    // COMBINE CIPHERTEXTS
    // ==========================================

    Point combinedC1 = add(C11, C21);
    Point combinedC2 = add(C12, C22);

    cout << "\n----- HOMOMORPHIC ADDITION -----" << endl;

    cout << "Combined C1: ";
    printPoint(combinedC1);
    cout << endl;

    cout << "Combined C2: ";
    printPoint(combinedC2);
    cout << endl;

    cout << "Combined Ciphertext: ";
    printPoint(combinedC1);
    cout << " , ";
    printPoint(combinedC2);
    cout << endl;


    // ==========================================
    // DECRYPT COMBINED CIPHERTEXT
    // ==========================================

    Point dCombinedC1 = multiply(combinedC1, d);

    Point negative_dCombinedC1 =
    {
        dCombinedC1.x,
        mod(-dCombinedC1.y)
    };

    Point decryptedCombinedM =
        add(combinedC2, negative_dCombinedC1);

    cout << "\n----- DECRYPT COMBINED CIPHERTEXT -----" << endl;

    cout << "d(Combined C1): ";
    printPoint(dCombinedC1);
    cout << endl;

    cout << "Decrypted combined message: ";
    printPoint(decryptedCombinedM);
    cout << endl;


    // ==========================================
    // ACTUAL M1 + M2
    // ==========================================

    Point expectedSum = add(M1, M2);

    cout << "\n----- CHECK -----" << endl;

    cout << "Actual M1 + M2: ";
    printPoint(expectedSum);
    cout << endl;


    return 0;
}