#include "keygen.h"
#include <random>
#include <unordered_set>
#include <stdexcept>
#include <algorithm>

using namespace std;

pair<int, int> genAfinKey(int m) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, m - 1);
    int a;
    do { a = dist(gen); } while (evk(a, m) != 1);
    uniform_int_distribution<> distB(0, m - 1);
    int b = distB(gen);
    return { a, b };
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
    if (!isPrime(p) || !isPrime(q) || p == q) return { 0, 0 };
    uint64_t n = p * q;
    uint64_t phi = (p - 1) * (q - 1);
    uint64_t e = 65537;
    if (evk64(e, phi) != 1) {
        for (e = 3; e < phi; e += 2)
            if (evk64(e, phi) == 1) break;
    }
    uint64_t d = extendEvk(e, phi, 'u');
    return { e, d };
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