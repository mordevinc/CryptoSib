#include "idea.h"
#include <cstring>

string ideaEncryptText(const string& text, const string& password) {
    if (password.empty()) return text;

    string result;
    size_t pwdLen = password.size();
    for (size_t i = 0; i < text.size(); i++) {
        result.push_back(text[i] ^ password[i % pwdLen]);
    }
    return result;
}

string ideaDecryptText(const string& cipher, const string& password) {
    return ideaEncryptText(cipher, password);
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
    return ideaEncryptFile(input, output, password);
}

// Заглушки для совместимости с .h
IDEAKey generateIDEAKey(const string& password) {
    IDEAKey key;
    memset(&key, 0, sizeof(key));
    return key;
}

IDEAKey generateInverseKey(const IDEAKey& key) {
    IDEAKey invKey;
    memset(&invKey, 0, sizeof(invKey));
    return invKey;
}

unsigned char ideaEncryptByte(unsigned char plain, const IDEAKey& key) {
    return plain;
}

unsigned char ideaDecryptByte(unsigned char cipher, const IDEAKey& key) {
    return cipher;
}