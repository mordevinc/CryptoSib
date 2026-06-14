#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

void rc4Init(const string& key, vector<unsigned char>& S) {
    S.resize(256);
    for (int i = 0; i < 256; i++) S[i] = i;
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
    for (char c : data) result.push_back(c ^ rc4Byte(S, i, j));
    return result;
}

bool rc4EncryptFile(const string& input, const string& output, const string& key) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty() && !fs::exists(outPath.parent_path()))
            fs::create_directories(outPath.parent_path());
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string encrypted = rc4Crypt(data, key);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.c_str(), encrypted.size());
        return true;
    } catch (...) { return false; }
}

bool rc4DecryptFile(const string& input, const string& output, const string& key) {
    return rc4EncryptFile(input, output, key);
}

#include <cstdint>
#include <random>
using namespace std;

int evk(int base, int mod) {
    int a = base, b = mod;
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

int extendEvk(int a, int b, char ret) {
    int oldU = 1, oldV = 0, u = 0, v = 1;
    int c = a, m = b;
    while (true) {
        int r = c % m, q = c / m;
        c = m; m = r;
        if (r <= 0) break;
        int tempU = u, tempV = v;
        u = oldU - q * tempU;
        v = oldV - q * tempV;
        oldU = tempU; oldV = tempV;
    }
    if (u < 0) u += b;
    if (ret == 'u') return u;
    if (ret == 'r') return c;
    if (ret == 'v') return v;
    return 0;
}

int sqrtZ(int m) {
    if (m < 0) return -1;
    if (m == 0 || m == 1) return m;
    for (int i = 1; i <= m / i; i++)
        if (i * i == m) return i;
    return -1;
}

uint64_t evk64(uint64_t base, uint64_t mod) {
    while (mod) { uint64_t t = mod; mod = base % mod; base = t; }
    return base;
}

uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result = 1;
    base %= mod;
    while (exp) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

bool isPrime(uint64_t n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    for (uint64_t i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

uint64_t generatePrime(int bits) {
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<uint64_t> dist(1ULL << (bits - 1), (1ULL << bits) - 1);
    uint64_t candidate;
    do {
        candidate = dist(gen);
        if (candidate % 2 == 0) candidate++;
    } while (!isPrime(candidate));
    return candidate;
}