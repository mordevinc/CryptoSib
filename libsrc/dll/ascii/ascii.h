#pragma once

#ifdef ASCII_EXPORTS
#define ASCII_API __declspec(dllexport)
#else
#define ASCII_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
using namespace std;
namespace fs = std::filesystem;

ASCII_API unsigned char encrAsciiByte(int shift, unsigned char x);
ASCII_API unsigned char decrAsciiByte(int shift, unsigned char y);
ASCII_API string encrAsciiText(const string& text, int shift);
ASCII_API string decrAsciiText(const string& text, int shift);
ASCII_API bool encrAsciiFile(const string& input, const string& output, int shift);
ASCII_API bool decrAsciiFile(const string& input, const string& output, int shift);