#pragma once
#pragma once

#ifdef PLEYFAIR_EXPORTS
#define PLEYFAIR_API __declspec(dllexport)
#else
#define PLEYFAIR_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <utility>
using namespace std;

// Основные функции шифрования Плейфера
PLEYFAIR_API unsigned char** genMatrixPleyfair(string key, int mod);
PLEYFAIR_API void deleteMatrix(unsigned char** matrix, int mod);
PLEYFAIR_API vector<string> genBigramsPleyfair(string text, unsigned char marker);
PLEYFAIR_API pair<int, int> findCoordSymbPleyfair(unsigned char** pm, unsigned char symb, int mod);
PLEYFAIR_API unsigned char findSymbForCoordPleyfair(unsigned char** pm, pair<int, int> coord, int mod);
PLEYFAIR_API vector<string> encrBigramsPleyfair(unsigned char** pm, vector<string> bigrams, int mod);
PLEYFAIR_API string encrTextPleyfair(vector<string> encrBigramsPleyfair);
PLEYFAIR_API vector<string> genEncrBigramsPleyfair(string encrTextPleyfair, unsigned char marker);
PLEYFAIR_API vector<string> decrBigramsPleyfair(unsigned char** pm, vector<string> encrBigramsPleyfair, int mod);
PLEYFAIR_API string decrTextPleyfair(vector<string> decrBigramsPleyfair, unsigned char marker);
PLEYFAIR_API void Pleyf(string key, string text, unsigned char marker, int mod);

// Функции для работы с файлами (HEX конвертация)
PLEYFAIR_API string fileToHex(const string& filename);
PLEYFAIR_API void hexToFile(const string& hex, const string& filename);
PLEYFAIR_API bool encrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod);
PLEYFAIR_API bool decrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod);