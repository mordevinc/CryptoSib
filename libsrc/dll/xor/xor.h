#pragma once

#ifdef XOR_EXPORTS
#define XOR_API __declspec(dllexport)
#else
#define XOR_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <cstdint>
using namespace std;
namespace fs = std::filesystem;

#pragma comment(lib, "mathFunction.lib")

extern "C" {
    uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod);
}

struct XORKey {
    uint16_t k[52];
};

XOR_API XORKey generateXORKey(const string& password);
XOR_API XORKey generateInverseKey(const XORKey& key);
XOR_API unsigned char XOREncryptByte(unsigned char plain, const XORKey& key);
XOR_API unsigned char XORDecryptByte(unsigned char cipher, const XORKey& key);
XOR_API string XOREncryptText(const string& text, const string& password);
XOR_API string XORDecryptText(const string& cipher, const string& password);
XOR_API bool XOREncryptFile(const string& input, const string& output, const string& password);
XOR_API bool XORDecryptFile(const string& input, const string& output, const string& password);