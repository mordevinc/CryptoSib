#pragma once

#ifdef IDEA_EXPORTS
#define IDEA_API __declspec(dllexport)
#else
#define IDEA_API __declspec(dllimport)
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

struct IDEAKey {
    uint16_t k[52];
};

IDEA_API IDEAKey generateIDEAKey(const string& password);
IDEA_API unsigned char ideaEncryptByte(unsigned char plain, const IDEAKey& key);
IDEA_API unsigned char ideaDecryptByte(unsigned char cipher, const IDEAKey& key);
IDEA_API string ideaEncryptText(const string& text, const string& password);
IDEA_API string ideaDecryptText(const string& cipher, const string& password);
IDEA_API bool ideaEncryptFile(const string& input, const string& output, const string& password);
IDEA_API bool ideaDecryptFile(const string& input, const string& output, const string& password);