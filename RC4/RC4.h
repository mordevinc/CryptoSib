#pragma once

#ifdef RC4_EXPORTS
#define RC4_API __declspec(dllexport)
#else
#define RC4_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
using namespace std;
namespace fs = std::filesystem;

RC4_API void rc4Init(const string& key, vector<unsigned char>& S);
RC4_API unsigned char rc4Byte(vector<unsigned char>& S, int& i, int& j);
RC4_API string rc4Crypt(const string& data, const string& key);
RC4_API bool rc4EncryptFile(const string& input, const string& output, const string& key);
RC4_API bool rc4DecryptFile(const string& input, const string& output, const string& key);