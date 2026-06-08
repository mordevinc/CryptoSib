#pragma once
#ifndef PERMUT_H
#define PERMUT_H

#include <string> 
#include <vector>

struct PermutationCipher {
    std::string key;
    std::vector<int> order;
};

void initPermutationCipher(PermutationCipher* cipher, const std::string& key);
void generateOrder(PermutationCipher* cipher);
std::vector<int> stringKeyToOrderPermutation(const std::string& strKey);
bool isNumericKeyPermutation(const std::string& key);

std::string encryptStringPermutation(const PermutationCipher* cipher, const std::string& text);
std::string decryptStringPermutation(const PermutationCipher* cipher, const std::string& ciphertext);

std::vector<char> encryptDataPermutation(const PermutationCipher* cipher, const std::vector<char>& data);
std::vector<char> decryptDataPermutation(const PermutationCipher* cipher, const std::vector<char>& data);

bool encryptFilePermutation(const PermutationCipher* cipher, const std::string& inputFile, const std::string& outputFile);
bool decryptFilePermutation(const PermutationCipher* cipher, const std::string& inputFile, const std::string& outputFile);

int getKeyLengthPermutation(const PermutationCipher* cipher);
std::string getKeyPermutation(const PermutationCipher* cipher);

#endif // PERMUT_H