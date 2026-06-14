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

//Генератор ключей для шифров
pair<int, int> genAfinKey(int m);
string genPleyfairKey(int m);
string genPleyfairKeyRead(int m);

#endif