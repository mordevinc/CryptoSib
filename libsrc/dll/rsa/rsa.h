#pragma once

#ifdef RSA_EXPORTS
#define RSA_API __declspec(dllexport)
#else
#define RSA_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <utility>
#include <cstdint>
using namespace std;
namespace fs = std::filesystem;

#pragma comment(lib, "mathFunction.lib")

extern "C" {
    uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod);
    uint64_t evk64(uint64_t base, uint64_t mod);
    int extendEvk(int a, int b, char ret);
    bool isPrime(uint64_t n);
}

RSA_API vector<uint64_t> encrRsaBlock(const string& text, uint64_t e, uint64_t n);
RSA_API string decrRsaBlock(const vector<uint64_t>& blocks, uint64_t d, uint64_t n);
RSA_API string encrRsaText(const string& text, uint64_t e, uint64_t n);
RSA_API string decrRsaText(const string& cipher, uint64_t d, uint64_t n);
RSA_API bool encrRsaFile(const string& input, const string& output, uint64_t e, uint64_t n);
RSA_API bool decrRsaFile(const string& input, const string& output, uint64_t d, uint64_t n);
RSA_API pair<uint64_t, uint64_t> genRsaKeys(uint64_t p, uint64_t q);