#pragma once
#pragma once
#define WIN32_LEAN_AND_MEAN           
#include <windows.h>
#ifdef AFFINE_EXPORTS
#define AFFINE_API __declspec(dllexport)
#else
#define AFFINE_API __declspec(dllimport)
#endif

#pragma comment(lib, "mathFunction.lib")

extern "C" {
    int evk(int base, int mod);
    int extendEvk(int a, int b, char ret);
}

#include <fstream>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <string>
using namespace std;
namespace fs = std::filesystem;

AFFINE_API unsigned char encrAffineByte(int a, int b, int m, unsigned char x);
AFFINE_API unsigned char decrAffineByte(int d, int b, int m, unsigned char y);
AFFINE_API bool isPrimeAM(int a, int m);
AFFINE_API string encrAffineText(const string& text, int a, int b, int m);
AFFINE_API string decrAffineText(const string& text, int a, int b, int m);
AFFINE_API bool encrAffineFile(const string& input, const string& output, int a, int b, int m);
AFFINE_API bool decrAffineFile(const string& input, const string& output, int a, int b, int m);