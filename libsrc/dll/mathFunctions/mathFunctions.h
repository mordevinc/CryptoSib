#pragma once
#define WIN32_LEAN_AND_MEAN           
#include <windows.h>
#include <cstdint>
#include <random>

using namespace std;

#ifdef MATH_EXPORTS
#define MATH_API __declspec(dllexport)
#else
#define MATH_API __declspec(dllimport)
#endif

extern "C" {
    MATH_API int evk(int base, int mod);
    MATH_API int extendEvk(int a, int b, char ret);
    MATH_API int sqrtZ(int m);

    MATH_API uint64_t evk64(uint64_t base, uint64_t mod);
    MATH_API uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod);
    MATH_API bool isPrime(uint64_t n);
    MATH_API uint64_t generatePrime(int bits);
}