#pragma once
#ifndef CRYPTO_H
#define CRYPTO_H
#include "../math/math.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <filesystem>
#include <random>
#include <chrono>

namespace fs = std::filesystem;
using namespace std;



//Функции Афинного шифра

unsigned char encrAffineByte(int a, int b, int m, unsigned char x);
unsigned char decrAffineByte(int d, int b, int m, unsigned char y);
bool isPrimeAM(int a, int m);
string encrAffineText(const string& text, int a, int b, int m);
string decrAffineText(const string& text, int a, int b, int m);
bool encrAffineFile(const string& input, const string& output, int a, int b, int m);
bool decrAffineFile(const string& input, const string& output, int a, int b, int m);

//Функции шифра Плейфера

unsigned char** genMatrixPleyfair(string key, int mod);
void deleteMatrix(unsigned char** matrix, int mod);
vector<string> genBigramsPleyfair(string text, unsigned char marker);
pair<int, int> findCoordSymbPleyfair(unsigned char** pm, unsigned char symb, int mod);
unsigned char findSymbForCoordPleyfair(unsigned char** pm, pair<int, int> coord, int mod);
vector<string> encrBigramsPleyfair(unsigned char** pm, vector<string> bigrams, int mod);
string encrTextPleyfair(vector<string> encrBigramsPleyfair);
vector<string> genEncrBigramsPleyfair(string encrTextPleyfair, unsigned char marker);
vector<string> decrBigramsPleyfair(unsigned char** pm, vector<string>encrBigramsPleyfair, int mod);
string decrTextPleyfair(vector<string> decrBigramsPleyfair, unsigned char marker);
void Pleyf(string key, string text, unsigned char marker, int mod);
string fileToHex(const string& filename);
void hexToFile(const string& hex, const string& filename);
bool encrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod);
bool decrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod);

// ШИФР ЦЕЗАРЯ
unsigned char encrCaesarByte(int shift, int m, unsigned char x);
unsigned char decrCaesarByte(int shift, int m, unsigned char y);
string encrCaesarText(const string& text, int shift, int m);
string decrCaesarText(const string& text, int shift, int m);
bool encrCaesarFile(const string& input, const string& output, int shift, int m);
bool decrCaesarFile(const string& input, const string& output, int shift, int m);

// RSA 
uint64_t modPow(uint64_t base, uint64_t exp, uint64_t mod);
vector<uint64_t> encrRsaBlock(const string& text, uint64_t e, uint64_t n);
string decrRsaBlock(const vector<uint64_t>& blocks, uint64_t d, uint64_t n);
string encrRsaText(const string& text, uint64_t e, uint64_t n);
string decrRsaText(const string& cipher, uint64_t d, uint64_t n);
bool encrRsaFile(const string& input, const string& output, uint64_t e, uint64_t n);
bool decrRsaFile(const string& input, const string& output, uint64_t d, uint64_t n);
pair<uint64_t, uint64_t> genRsaKeys(uint64_t p, uint64_t q);

// СДВИГ ПО ASCII
unsigned char encrAsciiByte(int shift, unsigned char x);
unsigned char decrAsciiByte(int shift, unsigned char y);
string encrAsciiText(const string& text, int shift);
string decrAsciiText(const string& text, int shift);
bool encrAsciiFile(const string& input, const string& output, int shift);
bool decrAsciiFile(const string& input, const string& output, int shift);

// XOR
struct XORKey {
    uint16_t k[52];
};
XORKey generateXORKey(const string& password);
unsigned char XOREncryptByte(unsigned char plain, const XORKey& key);
unsigned char XORDecryptByte(unsigned char cipher, const XORKey& key);
string XOREncryptText(const string& text, const string& password);
string XORDecryptText(const string& cipher, const string& password);
bool XOREncryptFile(const string& input, const string& output, const string& password);
bool XORDecryptFile(const string& input, const string& output, const string& password);

// RC4
void rc4Init(const string& key, vector<unsigned char>& S);
unsigned char rc4Byte(vector<unsigned char>& S, int& i, int& j);
string rc4Crypt(const string& data, const string& key);
bool rc4EncryptFile(const string& input, const string& output, const string& key);
bool rc4DecryptFile(const string& input, const string& output, const string& key);

// СТОЛБЦОВАЯ ПЕРЕСТАНОВКА
string encrPermutationText(const string& text, const vector<int>& key);
string decrPermutationText(const string& text, const vector<int>& key);
bool encrPermutationFile(const string& input, const string& output, const vector<int>& key);
bool decrPermutationFile(const string& input, const string& output, const vector<int>& key);

//Генератор ключей для шифров
pair<int, int> genAfinKey(int m);
string genPleyfairKey(int m);
string genPleyfairKeyRead(int m);
int genCaesarKey(int m);
int genAsciiKey();
string genXORKey(int length);
string genRc4Key(int length);
vector<int> genPermutationKey(int cols);

#endif