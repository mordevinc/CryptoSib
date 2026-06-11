#include "permut.h"
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

void initPermutationCipher(PermutationCipher* cipher, const string& key) {
    cipher->key = key;
    generateOrder(cipher);
}

void generateOrder(PermutationCipher* cipher) {
    cipher->order.clear();
    string key = cipher->key;
    int len = key.length();
    vector<pair<char, int>> temp;
    for (int i = 0; i < len; i++) {
        temp.push_back({key[i], i});
    }
    sort(temp.begin(), temp.end());
    for (int i = 0; i < len; i++) {
        cipher->order.push_back(temp[i].second);
    }
}

vector<int> stringKeyToOrderPermutation(const string& strKey) {
    vector<int> order;
    int len = strKey.length();
    vector<pair<char, int>> temp;
    for (int i = 0; i < len; i++) {
        temp.push_back({strKey[i], i});
    }
    sort(temp.begin(), temp.end());
    for (int i = 0; i < len; i++) {
        order.push_back(temp[i].second);
    }
    return order;
}

bool isNumericKeyPermutation(const string& key) {
    for (char c : key) {
        if (!isdigit(c)) return false;
    }
    return true;
}

string encryptStringPermutation(const PermutationCipher* cipher, const string& text) {
    int cols = cipher->order.size();
    int rows = ceil((double)text.length() / cols);
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));
    for (int i = 0; i < text.length(); i++) {
        matrix[i / cols][i % cols] = text[i];
    }
    string result;
    for (int k : cipher->order) {
        for (int r = 0; r < rows; r++) {
            if (matrix[r][k] != ' ') {
                result.push_back(matrix[r][k]);
            }
        }
    }
    return result;
}

string decryptStringPermutation(const PermutationCipher* cipher, const string& ciphertext) {
    int cols = cipher->order.size();
    int rows = ceil((double)ciphertext.length() / cols);
    int fullCols = ciphertext.length() % cols;
    if (fullCols == 0) fullCols = cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));
    int pos = 0;
    for (int k : cipher->order) {
        int limit = (k < fullCols) ? rows : rows - 1;
        for (int r = 0; r < limit; r++) {
            if (pos < ciphertext.length()) {
                matrix[r][k] = ciphertext[pos++];
            }
        }
    }
    string result;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (matrix[r][c] != ' ') {
                result.push_back(matrix[r][c]);
            }
        }
    }
    return result;
}

vector<char> encryptDataPermutation(const PermutationCipher* cipher, const vector<char>& data) {
    string str(data.begin(), data.end());
    string encrypted = encryptStringPermutation(cipher, str);
    return vector<char>(encrypted.begin(), encrypted.end());
}

vector<char> decryptDataPermutation(const PermutationCipher* cipher, const vector<char>& data) {
    string str(data.begin(), data.end());
    string decrypted = decryptStringPermutation(cipher, str);
    return vector<char>(decrypted.begin(), decrypted.end());
}

bool encryptFilePermutation(const PermutationCipher* cipher, const string& inputFile, const string& outputFile) {
    try {
        std::filesystem::path outPath(outputFile);
        if (!outPath.parent_path().empty()) {
            if (!std::filesystem::exists(outPath.parent_path())) {
                std::filesystem::create_directories(outPath.parent_path());
            }
        }
        ifstream in(inputFile, ios::binary);
        if (!in.is_open()) return false;
        vector<char> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        vector<char> encrypted = encryptDataPermutation(cipher, data);
        ofstream out(outputFile, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.data(), encrypted.size());
        return true;
    }
    catch (...) { return false; }
}

bool decryptFilePermutation(const PermutationCipher* cipher, const string& inputFile, const string& outputFile) {
    try {
        std::filesystem::path outPath(outputFile);
        if (!outPath.parent_path().empty()) {
            if (!std::filesystem::exists(outPath.parent_path())) {
                std::filesystem::create_directories(outPath.parent_path());
            }
        }
        ifstream in(inputFile, ios::binary);
        if (!in.is_open()) return false;
        vector<char> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        vector<char> decrypted = decryptDataPermutation(cipher, data);
        ofstream out(outputFile, ios::binary);
        if (!out.is_open()) return false;
        out.write(decrypted.data(), decrypted.size());
        return true;
    }
    catch (...) { return false; }
}

int getKeyLengthPermutation(const PermutationCipher* cipher) {
    return cipher->order.size();
}

string getKeyPermutation(const PermutationCipher* cipher) {
    return cipher->key;
}