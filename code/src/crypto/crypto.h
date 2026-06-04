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


using namespace std;

//Функции Афинного шифра

unsigned char encrAfinByte(int a, int b, int m, unsigned char x);
unsigned char decrAfinByte(int d, int b, int m, unsigned char y);
bool isProstAM(int a, int m);
bool encrAfinFile(const string& input, const string& output, int a, int b, int m);
bool decrAfinFile(const string& input, const string& output, int d, int b, int m);

//Функции шифра Плейфера

unsigned char** genMatrixPleyf(string key);
void deleteMatrix(unsigned char** matrix);
vector<string> genBigrams(string text, unsigned char marker);
pair<int, int> findCoordSymb(unsigned char** pm, unsigned char symb);
unsigned char findSymbForCoord(unsigned char** pm, pair<int, int> coord);
vector<string> encrBigrams(unsigned char** pm, vector<string> bigrams);
string encrText(vector<string> encrBigrams);
vector<string> genEncrBigrams(string encrText, unsigned char marker);
vector<string> decrBigrams(unsigned char** pm, vector<string>EncrBigrams);
string decrText(vector<string> decrBigrams, unsigned char marker);
void Pleyf(string key, string text, unsigned char marker);
string fileToHex(const string& filename);
void hexToFile(const string& hex, const string& filename);
bool encrPleyfFile(const string& input, const string& output, string key, unsigned char marker);
bool decrPleyfFile(const string& input, const string& output, string key, unsigned char marker);

#endif