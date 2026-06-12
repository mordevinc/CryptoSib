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

unsigned char encrAsciiByte(int shift, unsigned char x);
unsigned char decrAsciiByte(int shift, unsigned char y);
string encrAsciiText(const string& text, int shift);
string decrAsciiText(const string& text, int shift);
bool encrAsciiFile(const string& input, const string& output, int shift);
bool decrAsciiFile(const string& input, const string& output, int shift);

// СДВИГ ПО ASCII
unsigned char encrAsciiByte(int shift, unsigned char x);
unsigned char decrAsciiByte(int shift, unsigned char y);
string encrAsciiText(const string& text, int shift);
string decrAsciiText(const string& text, int shift);
bool encrAsciiFile(const string& input, const string& output, int shift);
bool decrAsciiFile(const string& input, const string& output, int shift);

// IDEA
struct IDEAKey {
    uint16_t k[52];
};
IDEAKey generateIDEAKey(const string& password);
unsigned char ideaEncryptByte(unsigned char plain, const IDEAKey& key);
unsigned char ideaDecryptByte(unsigned char cipher, const IDEAKey& key);
string ideaEncryptText(const string& text, const string& password);
string ideaDecryptText(const string& cipher, const string& password);
bool ideaEncryptFile(const string& input, const string& output, const string& password);
bool ideaDecryptFile(const string& input, const string& output, const string& password);

//Генератор ключей для шифров
pair<int, int> genAfinKey(int m);
string genPleyfairKey(int m);
string genPleyfairKeyRead(int m);

#endif