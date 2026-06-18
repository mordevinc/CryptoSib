#include "xor.h"
#include <cstring>

string XOREncryptText(const string& text, const string& password) {
    if (password.empty()) return text;

    string result;
    size_t pwdLen = password.size();
    for (size_t i = 0; i < text.size(); i++) {
        result.push_back(text[i] ^ password[i % pwdLen]);
    }
    return result;
}

string XORDecryptText(const string& cipher, const string& password) {
    return XOREncryptText(cipher, password);
}

bool XOREncryptFile(const string& input, const string& output, const string& password) {
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
        string encrypted = XOREncryptText(data, password);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.c_str(), encrypted.size());
        return true;
    }
    catch (...) { return false; }
}

bool XORDecryptFile(const string& input, const string& output, const string& password) {
    return XOREncryptFile(input, output, password);
}

// Заглушки для совместимости с .h
XORKey generateXORKey(const string& password) {
    XORKey key;
    memset(&key, 0, sizeof(key));
    return key;
}

XORKey generateInverseKey(const XORKey& key) {
    XORKey invKey;
    memset(&invKey, 0, sizeof(invKey));
    return invKey;
}

unsigned char XOREncryptByte(unsigned char plain, const XORKey& key) {
    return plain;
}

unsigned char XORDecryptByte(unsigned char cipher, const XORKey& key) {
    return cipher;
}