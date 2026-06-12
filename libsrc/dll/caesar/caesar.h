#pragma once

#ifdef CAESAR_EXPORTS
#define CAESAR_API __declspec(dllexport)
#else
#define CAESAR_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

#pragma comment(lib, "mathFunction.lib")

CAESAR_API unsigned char encrCaesarByte(int shift, int m, unsigned char x);
CAESAR_API unsigned char decrCaesarByte(int shift, int m, unsigned char y);
CAESAR_API string encrCaesarText(const string& text, int shift, int m);
CAESAR_API string decrCaesarText(const string& text, int shift, int m);
CAESAR_API bool encrCaesarFile(const string& input, const string& output, int shift, int m);
CAESAR_API bool decrCaesarFile(const string& input, const string& output, int shift, int m);