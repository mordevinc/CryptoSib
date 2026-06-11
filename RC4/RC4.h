#pragma once
#ifndef RC4_H
#define RC4_H

#ifdef RC4_EXPORTS
#define RC4_API __declspec(dllexport)
#else
#define RC4_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
#include <cstdint>

RC4_API void rc4InitState(uint8_t S[256], const std::string& key);
RC4_API void rc4InitStateBytes(uint8_t S[256], const uint8_t* key, size_t keyLen);
RC4_API void rc4ProcessData(uint8_t S[256], uint8_t* data, size_t length);
RC4_API void rc4ProcessVector(uint8_t S[256], std::vector<uint8_t>& data);

RC4_API std::string rc4EncryptText(const std::string& text, const std::string& key);
RC4_API std::string rc4DecryptText(const std::string& text, const std::string& key);

RC4_API bool rc4EncryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);
RC4_API bool rc4DecryptFile(const std::string& inputFile, const std::string& outputFile, const std::string& key);

RC4_API std::string rc4StringToHex(const std::string& str);
RC4_API std::string rc4HexToString(const std::string& hex);

RC4_API std::string rc4EncrText(const std::string& text, const std::string& key);
RC4_API std::string rc4DecrText(const std::string& text, const std::string& key);

RC4_API bool rc4EncrFile(const std::string& input, const std::string& output, const std::string& key);
RC4_API bool rc4DecrFile(const std::string& input, const std::string& output, const std::string& key);

#endif // RC4_H