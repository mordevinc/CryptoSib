#pragma once

#ifdef PERMUTATION_EXPORTS
#define PERMUTATION_API __declspec(dllexport)
#else
#define PERMUTATION_API __declspec(dllimport)
#endif

#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
namespace fs = std::filesystem;

PERMUTATION_API string encrPermutationText(const string& text, const vector<int>& key);
PERMUTATION_API string decrPermutationText(const string& text, const vector<int>& key);
PERMUTATION_API bool encrPermutationFile(const string& input, const string& output, const vector<int>& key);
PERMUTATION_API bool decrPermutationFile(const string& input, const string& output, const vector<int>& key);