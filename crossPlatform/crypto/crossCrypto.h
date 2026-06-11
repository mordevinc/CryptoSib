#pragma once
#ifndef CROSSCRYPTO_H
#define CROSSCRYPTO_H
#include "../../src/crypto/crypto.h"

//Функции Афинного шифра

string encrAffineHex(const string& hexText, int a, int b, int m);
string decrAffineHex(const string& hexCipher, int a, int b, int m);

//Функции преобразования принимаемой строки в HEX
string hexToStr(const string& hex);
string strToHex(const string& str);

#endif