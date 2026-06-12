#pragma once
#include <cstdint>

extern "C" {
    int evk(int base, int mod);
    int extendEvk(int a, int b, char ret);
    int sqrtZ(int m);
    
    uint64_t evk64(uint64_t base, uint64_t mod);
    uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod);
    bool isPrime(uint64_t n);
    uint64_t generatePrime(int bits);
}
