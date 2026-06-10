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
    string existFile(const string& operation);
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
};

#endif