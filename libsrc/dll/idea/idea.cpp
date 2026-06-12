#include "idea.h"
#include <cstring>

#define MUL(a, b) (uint16_t)(((uint32_t)(a) * (b)) % 65537)
#define ADD(a, b) (uint16_t)((a + b) & 0xFFFF)
#define XOR(a, b) (uint16_t)(a ^ b)

IDEAKey generateIDEAKey(const string& password) {
    IDEAKey key;
    uint16_t k[8];

    for (int i = 0; i < 8; i++) {
        if (i < password.size()) {
            k[i] = (uint16_t)((unsigned char)password[i]) << 8;
            if (i + 1 < password.size()) {
                k[i] |= (unsigned char)password[i + 1];
            }
        }
        else {
            k[i] = 0;
        }
    }

    for (int i = 0; i < 52; i++) {
        key.k[i] = k[i % 8];
        for (int j = 0; j < 8; j++) {
            if (i % 8 == 0 && j == 0) continue;
            k[j] = ((k[j] << 9) | (k[j] >> 7)) & 0xFFFF;
        }
    }

    return key;
}

unsigned char ideaEncryptByte(unsigned char plain, const IDEAKey& key) {
    uint16_t x = plain;

    for (int r = 0; r < 8; r++) {
        x = MUL(x, key.k[r * 6]);
        x = ADD(x, key.k[r * 6 + 1]);
        x = ADD(x, key.k[r * 6 + 2]);
        x = MUL(x, key.k[r * 6 + 3]);
        x = XOR(x, key.k[r * 6 + 4]);
        x = XOR(x, key.k[r * 6 + 5]);
    }

    x = MUL(x, key.k[48]);
    x = ADD(x, key.k[49]);
    x = ADD(x, key.k[50]);
    x = MUL(x, key.k[51]);

    return (unsigned char)(x & 0xFF);
}

unsigned char ideaDecryptByte(unsigned char cipher, const IDEAKey& key) {
    return ideaEncryptByte(cipher, key);
}

string ideaEncryptText(const string& text, const string& password) {
    IDEAKey key = generateIDEAKey(password);
    string result;
    for (unsigned char c : text) {
        result.push_back(ideaEncryptByte(c, key));
    }
    return result;
}

string ideaDecryptText(const string& cipher, const string& password) {
    IDEAKey key = generateIDEAKey(password);
    string result;
    for (unsigned char c : cipher) {
        result.push_back(ideaDecryptByte(c, key));
    }
    return result;
}

bool ideaEncryptFile(const string& input, const string& output, const string& password) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string encrypted = ideaEncryptText(data, password);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.c_str(), encrypted.size());
        return true;
    }
    catch (...) { return false; }
}

bool ideaDecryptFile(const string& input, const string& output, const string& password) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string decrypted = ideaDecryptText(data, password);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(decrypted.c_str(), decrypted.size());
        return true;
    }
    catch (...) { return false; }
}