#pragma once

#ifdef KEYGEN_EXPORTS
#define KEYGEN_API __declspec(dllexport)
#else
#define KEYGEN_API __declspec(dllimport)
#endif

#include <string>
#include <utility>
using namespace std;

KEYGEN_API pair<int, int> genAfinKey(int m);
KEYGEN_API string genPleyfairKey(int m);
KEYGEN_API string genPleyfairKeyRead(int m);
