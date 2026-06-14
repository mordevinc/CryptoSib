#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <iomanip>
#include <stdexcept>
using namespace std;
namespace fs = std::filesystem;

extern "C" { int sqrtZ(int m); }

unsigned char** genMatrixPleyfair(string key, int mod) {
    int m = sqrtZ(mod);
    unsigned char** mp = new unsigned char*[m];
    for (int i = 0; i < m; i++) mp[i] = new unsigned char[m];
    unordered_set<unsigned char> used;
    int i = 0, j = 0;
    for (unsigned char item : key) {
        if (used.find(item) == used.end()) {
            mp[i][j] = item;
            used.insert(item);
            if (++j == m) { j = 0; i++; }
            if (i == m) return mp;
        }
    }
    for (unsigned char symb = 0; symb < mod - 1; symb++) {
        if (used.find(symb) == used.end()) {
            mp[i][j] = symb;
            used.insert(symb);
            if (++j == m) { j = 0; i++; }
        }
    }
    if (used.find(mod - 1) == used.end()) mp[i][j] = mod - 1;
    return mp;
}

void deleteMatrix(unsigned char** matrix, int mod) {
    int m = sqrtZ(mod);
    for (int i = 0; i < m; i++) delete[] matrix[i];
    delete[] matrix;
}

vector<string> genBigramsPleyfair(string text, unsigned char marker) {
    vector<string> bigrams;
    for (size_t i = 0; i < text.size(); i++) {
        string bg;
        if (i + 1 >= text.size() || text[i] == text[i + 1]) {
            bg.push_back(text[i]); bg.push_back(marker);
            bigrams.push_back(bg);
            text.erase(i, 1);
            i--;
        } else {
            bg.push_back(text[i]); bg.push_back(text[i + 1]);
            bigrams.push_back(bg);
            text.erase(i, 2);
            if (i == 0) i--;
            else i -= 2;
        }
    }
    return bigrams;
}

pair<int, int> findCoordSymbPleyfair(unsigned char** pm, unsigned char symb, int mod) {
    int m = sqrtZ(mod);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
            if (pm[i][j] == symb) return {i, j};
    return {-1, -1};
}

unsigned char findSymbForCoordPleyfair(unsigned char** pm, pair<int, int> coord, int mod) {
    int m = sqrtZ(mod);
    return (coord.first < m && coord.second < m) ? pm[coord.first][coord.second] : 0;
}

vector<string> encrBigramsPleyfair(unsigned char** pm, vector<string> bigrams, int mod) {
    int m = sqrtZ(mod);
    vector<string> result;
    for (string item : bigrams) {
        unsigned char a = item[0], b = item[1];
        auto [ax, ay] = findCoordSymbPleyfair(pm, a, mod);
        auto [bx, by] = findCoordSymbPleyfair(pm, b, mod);
        if (ax == bx) { ay = (ay + 1) % m; by = (by + 1) % m; }
        else if (ay == by) { ax = (ax + 1) % m; bx = (bx + 1) % m; }
        else swap(ay, by);
        string encr;
        encr.push_back(findSymbForCoordPleyfair(pm, {ax, ay}, mod));
        encr.push_back(findSymbForCoordPleyfair(pm, {bx, by}, mod));
        result.push_back(encr);
    }
    return result;
}

string encrTextPleyfair(vector<string> encrBigrams) {
    string result;
    for (string s : encrBigrams) result += s;
    return result;
}

vector<string> genEncrBigramsPleyfair(string encrText, unsigned char marker) {
    return genBigramsPleyfair(encrText, marker);
}

vector<string> decrBigramsPleyfair(unsigned char** pm, vector<string> encrBigrams, int mod) {
    int m = sqrtZ(mod);
    vector<string> result;
    for (string item : encrBigrams) {
        unsigned char a = item[0], b = item[1];
        auto [ax, ay] = findCoordSymbPleyfair(pm, a, mod);
        auto [bx, by] = findCoordSymbPleyfair(pm, b, mod);
        if (ax == bx) { ay = (ay - 1 + m) % m; by = (by - 1 + m) % m; }
        else if (ay == by) { ax = (ax - 1 + m) % m; bx = (bx - 1 + m) % m; }
        else swap(ay, by);
        string decr;
        decr.push_back(findSymbForCoordPleyfair(pm, {ax, ay}, mod));
        decr.push_back(findSymbForCoordPleyfair(pm, {bx, by}, mod));
        result.push_back(decr);
    }
    return result;
}

string decrTextPleyfair(vector<string> decrBigrams, unsigned char marker) {
    string result;
    for (string s : decrBigrams)
        for (unsigned char c : s)
            if (c != marker) result.push_back(c);
    return result;
}

string fileToHex(const string& filename) {
    ifstream in(filename, ios::binary);
    if (!in) throw runtime_error("Cannot open file");
    string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    ostringstream oss;
    oss << hex << setfill('0');
    for (unsigned char c : data) oss << setw(2) << (int)c;
    return oss.str();
}

void hexToFile(const string& hex, const string& filename) {
    ofstream out(filename, ios::binary);
    if (!out) throw runtime_error("Cannot create file");
    for (size_t i = 0; i < hex.size(); i += 2) {
        char byte = (char)stoi(hex.substr(i, 2), nullptr, 16);
        out.put(byte);
    }
}

bool encrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod) {
    try {
        string hex = fileToHex(input);
        unsigned char** pm = genMatrixPleyfair(key, mod);
        auto bgr = genBigramsPleyfair(hex, marker);
        auto encrBgr = encrBigramsPleyfair(pm, bgr, mod);
        string encr = encrTextPleyfair(encrBgr);
        ofstream out(output, ios::binary);
        out.write(encr.c_str(), encr.size());
        deleteMatrix(pm, mod);
        return true;
    } catch (...) { return false; }
}

bool decrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod) {
    try {
        unsigned char** pm = genMatrixPleyfair(key, mod);
        ifstream in(input, ios::binary);
        string encrData((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        auto encrBgr = genEncrBigramsPleyfair(encrData, marker);
        auto decrBgr = decrBigramsPleyfair(pm, encrBgr, mod);
        string decrHex = decrTextPleyfair(decrBgr, marker);
        hexToFile(decrHex, output);
        deleteMatrix(pm, mod);
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