#pragma once
#ifndef CROSSMENU_H
#define CROSSMENU_H

#include "../crypto/crossCrypto.h"
#include "../../src/menu/menu.h"

class CrossPlatform {

public:
    void crosspShowMenu();

private:
    int getChoice(int min, int max, const string& prompt);

    void choiceFuncOfTextAffine();
    void choiceFuncOfTextPleyfair();
    void choiceFuncOfFileAffine();
    void choiceFuncOfFilePleyfair();

    void choiceFuncOfText();
    void choiceFuncOfFile();
    void choiceKeyGen();

    // Вспомогательные функции
    int showTextOperations();
    int showFileOperations();
    string checkText();
    string existFile(const string& operation, const string& dir);
    string accessCreateDirForSaveFile(const string& operation, const string& dir);

    // Афинный шифр
    uint64_t checkKeyAffine();
    void enterTextToEncryptAffine(uint64_t a, uint64_t b, int mod);
    void enterTextToDecryptAffine(uint64_t a, uint64_t b, int mod);
    void enterFileToEncryptAffine(uint64_t a, uint64_t b, int mod);
    void enterFileToDecryptAffine(uint64_t a, uint64_t b, int mod);

    // Плейфер
    string checkKeyPleyfair();
    unsigned char checkMarkerPleyfair();
    void enterTextToEncryptPleyfair(const string& key, unsigned char marker, int mod);
    void enterTextToDecryptPleyfair(const string& key, unsigned char marker, int mod);
    void enterFileToEncryptPleyfair(const string& key, unsigned char marker, int mod);
    void enterFileToDecryptPleyfair(const string& key, unsigned char marker, int mod);

    // Caesar
    uint64_t checkKeyCaesar();
    void enterTextToEncryptCaesar(uint64_t shift, int mod);
    void enterTextToDecryptCaesar(uint64_t shift, int mod);
    void enterFileToEncryptCaesar(uint64_t shift, int mod);
    void enterFileToDecryptCaesar(uint64_t shift, int mod);
    void choiceFuncOfTextCaesar();
    void choiceFuncOfFileCaesar();

    // RSA
    void enterTextToEncryptRsa(uint64_t e, uint64_t n);
    void enterTextToDecryptRsa(uint64_t d, uint64_t n);
    void enterFileToEncryptRsa(uint64_t e, uint64_t n);
    void enterFileToDecryptRsa(uint64_t d, uint64_t n);
    void choiceFuncOfTextRsa();
    void choiceFuncOfFileRsa();
    void choiceKeyGenRsa();

    // ASCII
    int checkKeyAscii();
    void enterTextToEncryptAscii(int shift);
    void enterTextToDecryptAscii(int shift);
    void enterFileToEncryptAscii(int shift);
    void enterFileToDecryptAscii(int shift);
    void choiceFuncOfTextAscii();
    void choiceFuncOfFileAscii();

    // XOR
    string checkKeyXOR();
    void enterTextToEncryptXOR(const string& password);
    void enterTextToDecryptXOR(const string& password);
    void enterFileToEncryptXOR(const string& password);
    void enterFileToDecryptXOR(const string& password);
    void choiceFuncOfTextXOR();
    void choiceFuncOfFileXOR();

    // RC4
    string checkKeyRc4();
    void enterTextToEncryptRc4(const string& key);
    void enterTextToDecryptRc4(const string& key);
    void enterFileToEncryptRc4(const string& key);
    void enterFileToDecryptRc4(const string& key);
    void choiceFuncOfTextRc4();
    void choiceFuncOfFileRc4();

    // Перестановка
    vector<int> checkKeyPermutation();
    void enterTextToEncryptPermutation(const vector<int>& key);
    void enterTextToDecryptPermutation(const vector<int>& key);
    void enterFileToEncryptPermutation(const vector<int>& key);
    void enterFileToDecryptPermutation(const vector<int>& key);
    void choiceFuncOfTextPermutation();
    void choiceFuncOfFilePermutation();


    void choiceKeyGenCaesar();
    void choiceKeyGenAscii();
    void choiceKeyGenXOR();
    void choiceKeyGenRc4();
    void choiceKeyGenPermutation();
};

#endif