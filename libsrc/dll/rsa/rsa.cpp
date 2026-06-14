#include "rsa.h"
#include <stdexcept>

vector<uint64_t> encrRsaBlock(const string& text, uint64_t e, uint64_t n) {
    vector<uint64_t> blocks;
    for (unsigned char c : text) {
        blocks.push_back(modPow(c, e, n));
    }
    return blocks;
}

string decrRsaBlock(const vector<uint64_t>& blocks, uint64_t d, uint64_t n) {
    string result;
    for (uint64_t block : blocks) {
        result.push_back((char)modPow(block, d, n));
    }
    return result;
}

string encrRsaText(const string& text, uint64_t e, uint64_t n) {
    vector<uint64_t> blocks = encrRsaBlock(text, e, n);
    string result;
    for (uint64_t block : blocks) {
        result += to_string(block) + " ";
    }
    return result;
}

string decrRsaText(const string& cipher, uint64_t d, uint64_t n) {
    vector<uint64_t> blocks;
    stringstream ss(cipher);
    uint64_t block;
    while (ss >> block) {
        blocks.push_back(block);
    }
    return decrRsaBlock(blocks, d, n);
}

bool encrRsaFile(const string& input, const string& output, uint64_t e, uint64_t n) {
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
        string encrypted = encrRsaText(data, e, n);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.c_str(), encrypted.size());
        return true;
    }
    catch (...) { return false; }
}

bool decrRsaFile(const string& input, const string& output, uint64_t d, uint64_t n) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string cipher((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string decrypted = decrRsaText(cipher, d, n);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(decrypted.c_str(), decrypted.size());
        return true;
    }
    catch (...) { return false; }
}

pair<uint64_t, uint64_t> genRsaKeys(uint64_t p, uint64_t q) {
    // Проверка, что p и q — простые числа
    if (!isPrime(p)) {
        throw runtime_error("p не является простым числом: " + to_string(p));
    }
    if (!isPrime(q)) {
        throw runtime_error("q не является простым числом: " + to_string(q));
    }
    if (p == q) {
        throw runtime_error("p и q должны быть разными простыми числами");
    }

    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    uint64_t e = 65537;

    if (evk64(e, phi) != 1) {
        for (e = 3; e < phi; e += 2) {
            if (evk64(e, phi) == 1) break;
        }
    }

    uint64_t d = extendEvk(static_cast<int>(e), static_cast<int>(phi), 'u');
    return { e, d };
}