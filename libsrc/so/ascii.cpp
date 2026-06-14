#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

unsigned char encrAsciiByte(int shift, unsigned char x) {
    return (unsigned char)((x + shift) % 256);
}

unsigned char decrAsciiByte(int shift, unsigned char y) {
    return (unsigned char)((y - shift + 256) % 256);
}

string encrAsciiText(const string& text, int shift) {
    string result;
    for (unsigned char c : text) result.push_back(encrAsciiByte(shift, c));
    return result;
}

string decrAsciiText(const string& text, int shift) {
    string result;
    for (unsigned char c : text) result.push_back(decrAsciiByte(shift, c));
    return result;
}

bool encrAsciiFile(const string& input, const string& output, int shift) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty() && !fs::exists(outPath.parent_path()))
            fs::create_directories(outPath.parent_path());
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        char byte;
        while (in.get(byte)) out.put(encrAsciiByte(shift, (unsigned char)byte));
        return true;
    } catch (...) { return false; }
}

bool decrAsciiFile(const string& input, const string& output, int shift) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty() && !fs::exists(outPath.parent_path()))
            fs::create_directories(outPath.parent_path());
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        char byte;
        while (in.get(byte)) out.put(decrAsciiByte(shift, (unsigned char)byte));
        return true;
    } catch (...) { return false; }
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