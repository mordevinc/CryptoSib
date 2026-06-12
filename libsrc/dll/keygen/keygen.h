#pragma once

#ifdef KEYGEN_EXPORTS
#define KEYGEN_API __declspec(dllexport)
#else
#define KEYGEN_API __declspec(dllimport)
#endif

#include <string>
#include <utility>
#include <vector>
#include <cstdint>
using namespace std;

#pragma comment(lib, "mathFunction.lib")

extern "C" {
    int evk(int base, int mod);
    int sqrtZ(int m);
    int extendEvk(int a, int b, char ret);
    uint64_t evk64(uint64_t base, uint64_t mod);
    uint64_t generatePrime(int bits);
    bool isPrime(uint64_t n);
}

KEYGEN_API pair<int, int> genAfinKey(int m);
KEYGEN_API string genPleyfairKey(int m);
KEYGEN_API string genPleyfairKeyRead(int m);
KEYGEN_API pair<uint64_t, uint64_t> genRsaKeys(uint64_t p, uint64_t q);
KEYGEN_API void genRsaKeyPair(uint64_t& e, uint64_t& d, uint64_t& n);

KEYGEN_API int genCaesarKey(int m);
KEYGEN_API int genAsciiKey();
KEYGEN_API string genIdeaKey(int length);
KEYGEN_API string genRc4Key(int length);
KEYGEN_API vector<int> genPermutationKey(int cols);