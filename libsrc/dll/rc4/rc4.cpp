#include "rc4.h"

void rc4Init(const string& key, vector<unsigned char>& S) {
    S.resize(256);
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;
        swap(S[i], S[j]);
    }
}

unsigned char rc4Byte(vector<unsigned char>& S, int& i, int& j) {
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    swap(S[i], S[j]);
    return S[(S[i] + S[j]) % 256];
}

string rc4Crypt(const string& data, const string& key) {
    vector<unsigned char> S;
    rc4Init(key, S);
    int i = 0, j = 0;
    string result;
    for (char c : data) {
        result.push_back(c ^ rc4Byte(S, i, j));
    }
    return result;
}

bool rc4EncryptFile(const string& input, const string& output, const string& key) {
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
        string encrypted = rc4Crypt(data, key);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.c_str(), encrypted.size());
        return true;
    }
    catch (...) { return false; }
}

bool rc4DecryptFile(const string& input, const string& output, const string& key) {
    return rc4EncryptFile(input, output, key);
}