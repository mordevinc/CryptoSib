#include <string>
#include <utility>
#include <vector>
#include <random>
#include <unordered_set>
#include <algorithm>
#include <cstdint>
using namespace std;

extern "C" {
    int evk(int base, int mod);
    int sqrtZ(int m);
    int extendEvk(int a, int b, char ret);
    uint64_t evk64(uint64_t base, uint64_t mod);
    uint64_t generatePrime(int bits);
    bool isPrime(uint64_t n);
}

pair<int, int> genAfinKey(int m) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, m - 1);
    int a;
    do { a = dist(gen); } while (evk(a, m) != 1);
    uniform_int_distribution<> distB(0, m - 1);
    int b = distB(gen);
    return {a, b};
}

string genPleyfairKey(int m) {
    int len = sqrtZ(m);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, m - 1);
    unordered_set<unsigned char> used;
    string key;
    while (key.size() < len) {
        unsigned char ch = dist(gen);
        if (used.find(ch) == used.end()) {
            used.insert(ch);
            key += ch;
        }
    }
    return key;
}

string genPleyfairKeyRead(int m) {
    int len = sqrtZ(m);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(32, 126);
    unordered_set<unsigned char> used;
    string key;
    while (key.size() < len) {
        unsigned char ch = dist(gen);
        if (used.find(ch) == used.end()) {
            used.insert(ch);
            key += ch;
        }
    }
    return key;
}

pair<uint64_t, uint64_t> genRsaKeys(uint64_t p, uint64_t q) {
    if (!isPrime(p) || !isPrime(q) || p == q) return {0, 0};
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    uint64_t e = 65537;
    if (evk64(e, phi) != 1) {
        for (e = 3; e < phi; e += 2)
            if (evk64(e, phi) == 1) break;
    }
    uint64_t d = extendEvk(e, phi, 'u');
    return {e, d};
}

void genRsaKeyPair(uint64_t& e, uint64_t& d, uint64_t& n) {
    uint64_t p = generatePrime(16);
    uint64_t q = generatePrime(16);
    n = p * q;
    auto keys = genRsaKeys(p, q);
    e = keys.first;
    d = keys.second;
}

int genCaesarKey(int m) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, m - 1);
    return dist(gen);
}

int genAsciiKey() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 255);
    return dist(gen);
}

string genIdeaKey(int length) {
    if (length <= 0) length = 16;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(32, 126);
    string key;
    for (int i = 0; i < length; i++) {
        key.push_back((char)dist(gen));
    }
    return key;
}

string genRc4Key(int length) {
    return genIdeaKey(length);
}

vector<int> genPermutationKey(int cols) {
    if (cols <= 0) cols = 5;
    random_device rd;
    mt19937 gen(rd());
    vector<int> key(cols);
    for (int i = 0; i < cols; i++) {
        key[i] = i;
    }
    for (int i = cols - 1; i > 0; i--) {
        uniform_int_distribution<> dist(0, i);
        int j = dist(gen);
        swap(key[i], key[j]);
    }
    return key;
}

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