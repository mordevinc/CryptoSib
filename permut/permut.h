#pragma once
#ifndef PERMUTATION_H
#define PERMUTATION_H

#ifdef PERMUTATION_EXPORTS
#define PERMUTATION_API __declspec(dllexport)
#else
#define PERMUTATION_API __declspec(dllimport)
#endif

#include <string>
#include <vector>

struct PermutationCipher {
    std::string key;
    std::vector<int> order;
};

PERMUTATION_API void initPermutationCipher(PermutationCipher* cipher, const std::string& key);
PERMUTATION_API void generateOrder(PermutationCipher* cipher);
PERMUTATION_API std::vector<int> stringKeyToOrderPermutation(const std::string& strKey);
PERMUTATION_API bool isNumericKeyPermutation(const std::string& key);

PERMUTATION_API std::string encryptStringPermutation(const PermutationCipher* cipher, const std::string& text);
PERMUTATION_API std::string decryptStringPermutation(const PermutationCipher* cipher, const std::string& ciphertext);

PERMUTATION_API std::vector<char> encryptDataPermutation(const PermutationCipher* cipher, const std::vector<char>& data);
PERMUTATION_API std::vector<char> decryptDataPermutation(const PermutationCipher* cipher, const std::vector<char>& data);

PERMUTATION_API bool encryptFilePermutation(const PermutationCipher* cipher, const std::string& inputFile, const std::string& outputFile);
PERMUTATION_API bool decryptFilePermutation(const PermutationCipher* cipher, const std::string& inputFile, const std::string& outputFile);

PERMUTATION_API int getKeyLengthPermutation(const PermutationCipher* cipher);
PERMUTATION_API std::string getKeyPermutation(const PermutationCipher* cipher);

#endif // PERMUTATION_H