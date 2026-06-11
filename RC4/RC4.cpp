#include "rc4.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

void rc4InitState(uint8_t S[256], const string& key) {
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;
        uint8_t temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

void rc4InitStateBytes(uint8_t S[256], const uint8_t* key, size_t keyLen) {
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % keyLen]) % 256;
        uint8_t temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

void rc4ProcessData(uint8_t S[256], uint8_t* data, size_t length) {
    int i = 0, j = 0;
    for (size_t n = 0; n < length; n++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        uint8_t temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        data[n] ^= S[(S[i] + S[j]) % 256];
    }
}

void rc4ProcessVector(uint8_t S[256], vector<uint8_t>& data) {
    rc4ProcessData(S, data.data(), data.size());
}

string rc4EncryptText(const string& text, const string& key) {
    uint8_t S[256];
    rc4InitState(S, key);
    vector<uint8_t> data(text.begin(), text.end());
    rc4ProcessVector(S, data);
    return string(data.begin(), data.end());
}

string rc4DecryptText(const string& text, const string& key) {
    return rc4EncryptText(text, key);
}

bool rc4EncryptFile(const string& inputFile, const string& outputFile, const string& key) {
    try {
        std::filesystem::path outPath(outputFile);
        if (!outPath.parent_path().empty()) {
            if (!std::filesystem::exists(outPath.parent_path())) {
                std::filesystem::create_directories(outPath.parent_path());
            }
        }
        ifstream in(inputFile, ios::binary);
        if (!in.is_open()) return false;
        vector<uint8_t> data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        uint8_t S[256];
        rc4InitState(S, key);
        rc4ProcessVector(S, data);
        ofstream out(outputFile, ios::binary);
        if (!out.is_open()) return false;
        out.write(reinterpret_cast<const char*>(data.data()), data.size());
        return true;
    }
    catch (...) { return false; }
}

bool rc4DecryptFile(const string& inputFile, const string& outputFile, const string& key) {
    return rc4EncryptFile(inputFile, outputFile, key);
}

string rc4StringToHex(const string& str) {
    stringstream ss;
    ss << hex << setfill('0');
    for (unsigned char c : str) {
        ss << setw(2) << (int)c;
    }
    return ss.str();
}

string rc4HexToString(const string& hex) {
    string result;
    for (size_t i = 0; i < hex.size(); i += 2) {
        if (i + 1 >= hex.size()) break;
        char byte = static_cast<char>(stoi(hex.substr(i, 2), nullptr, 16));
        result.push_back(byte);
    }
    return result;
}

string rc4EncrText(const string& text, const string& key) {
    return rc4EncryptText(text, key);
}

string rc4DecrText(const string& text, const string& key) {
    return rc4DecryptText(text, key);
}

bool rc4EncrFile(const string& input, const string& output, const string& key) {
    return rc4EncryptFile(input, output, key);
}

bool rc4DecrFile(const string& input, const string& output, const string& key) {
    return rc4DecryptFile(input, output, key);
}