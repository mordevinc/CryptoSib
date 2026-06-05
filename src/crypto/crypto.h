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

namespace fs = std::filesystem;
using namespace std;

int sqrtZ(int m);

//Функции Афинного шифра

unsigned char encrAfinByte(int a, int b, int m, unsigned char x);
unsigned char decrAfinByte(int d, int b, int m, unsigned char y);
bool isPrimeAM(int a, int m);
string encrAffineText(const string& text, int a, int b, int m);
string decrAffineText(const string& text, int a, int b, int m);
bool encrAfinFile(const string& input, const string& output, int a, int b, int m);
bool decrAfinFile(const string& input, const string& output, int a, int b, int m);

//Функции шифра Плейфера

unsigned char** genMatrixPleyf(string key, int mod);
void deleteMatrix(unsigned char** matrix, int mod);
vector<string> genBigrams(string text, unsigned char marker);
pair<int, int> findCoordSymb(unsigned char** pm, unsigned char symb, int mod);
unsigned char findSymbForCoord(unsigned char** pm, pair<int, int> coord, int mod);
vector<string> encrBigrams(unsigned char** pm, vector<string> bigrams, int mod);
string encrText(vector<string> encrBigrams);
vector<string> genEncrBigrams(string encrText, unsigned char marker);
vector<string> decrBigrams(unsigned char** pm, vector<string>EncrBigrams, int mod);
string decrText(vector<string> decrBigrams, unsigned char marker);
void Pleyf(string key, string text, unsigned char marker, int mod);
string fileToHex(const string& filename);
void hexToFile(const string& hex, const string& filename);
bool encrPleyfFile(const string& input, const string& output, string key, unsigned char marker, int mod);
bool decrPleyfFile(const string& input, const string& output, string key, unsigned char marker, int mod);
#endif