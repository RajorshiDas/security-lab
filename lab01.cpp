#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Convert a string to binary (8 bits per character)
string toBinary(string text) {
    string binary = "";
    for (char ch : text) {
        for (int b = 7; b >= 0; b--) {
            binary += ((ch >> b) & 1) ? '1' : '0';
        }
    }
    return binary;
}

// Convert binary back to text
string toText(string binary) {
    string text = "";
    for (int i = 0; i < binary.length(); i += 8) {
        string byte = binary.substr(i, 8);
        char ch = 0;
        for (int j = 0; j < 8; j++) {
            ch = ch << 1;
            if (byte[j] == '1') ch = ch | 1;
        }
        text += ch;
    }
    return text;
}

// Generate a random binary key of given length
string generateKey(int length) {
    string key = "";
    for (int i = 0; i < length; i++) {
        key += (rand() % 2 == 0) ? '0' : '1';
    }
    return key;
}

// XOR two binary strings
string xorStrings(string a, string b) {
    string result = "";
    for (int i = 0; i < a.length(); i++) {
        result += (a[i] == b[i]) ? '0' : '1';
    }
    return result;
}

// Transpose any m x n matrix (rows <-> columns)
vector<vector<string>> transposeMatrix(vector<vector<string>> matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<vector<string>> result(cols, vector<string>(rows));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j][i] = matrix[i][j];
        }
    }
    return result;
}

// Print a matrix
void printMatrix(vector<vector<string>> matrix, string label) {
    cout << "\n" << label << "\n";
    for (auto row : matrix) {
        for (auto val : row) cout << val << " ";
        cout << endl;
    }
}

int main() {
    srand(time(0));

    vector<vector<string>> matrix = {
        {"cse", "21"},
        {"kuet", "khulna"}
    };
    printMatrix(matrix, "Original Matrix:");

    // Step 1: Transpose
    vector<vector<string>> transposed = transposeMatrix(matrix);
    printMatrix(transposed, "Transposed Matrix:");

    int rows = transposed.size();
    int cols = transposed[0].size();

    // Step 2, 3, 4: binary -> key -> XOR (encryption)
    vector<vector<string>> binaryMatrix(rows, vector<string>(cols));
    vector<vector<string>> keyMatrix(rows, vector<string>(cols));
    vector<vector<string>> cipherMatrix(rows, vector<string>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            binaryMatrix[i][j] = toBinary(transposed[i][j]);
            keyMatrix[i][j] = generateKey(binaryMatrix[i][j].length());
            cipherMatrix[i][j] = xorStrings(binaryMatrix[i][j], keyMatrix[i][j]);
        }
    }

    printMatrix(binaryMatrix, "Binary Matrix:");
    printMatrix(keyMatrix, "Key Matrix:");
    printMatrix(cipherMatrix, "Encrypted (Cipher) Matrix:");

    // Step 5: Decryption (XOR cipher with same key)
    vector<vector<string>> decryptedMatrix(rows, vector<string>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            string binaryBack = xorStrings(cipherMatrix[i][j], keyMatrix[i][j]);
            decryptedMatrix[i][j] = toText(binaryBack);
        }
    }

    printMatrix(decryptedMatrix, "Decrypted Matrix:");

    return 0;
}