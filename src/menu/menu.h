#pragma once
#ifndef MENU_H
#define MENU_H
#include "../crypto/crypto.h"
// Платформозависимые заголовки
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 
#define NOGDI                
#include <windows.h>
#pragma comment(lib, "src/dll/mathFunction.lib")
#pragma comment(lib, "src/dll/affine.lib")
#pragma comment(lib, "src/dll/pleyfair.lib")
#pragma comment(lib, "src/dll/keygen.lib")
#endif

const unsigned int MODULE = 256;
#define INPUT_DIR   "files/input/"
#define ENCR_DIR  "files/encryption/"
#define DECR_DIR  "files/decryption/"

enum class FunctionsOfProgram {
	TEXT = 1,
	FILE,
	KEY,
	OFF
};
enum class Algorithms {
	AFFINE = 1,
	PLAYFAIR,
	PERMUT,
	RC4,
	ASCII,
	IDEA,
	RSA,
	CESAR
};
enum class FunctionsOfText {
	ENCRYPT_TEXT = 1,
	DECRYPT_TEXT
};
enum class FunctionsOfFile {
	ENCRYPT_FILE = 1,
	DECRYPT_FILE
};

// Установка кодировки консоли
void setConsoleEncoding();


class Windows {

public:
	void showMenu();
	
private:
	int getChoice(int min, int max, const string& prompt);
	void choiceFuncOfTextAffine();
	void choiceFuncOfTextPleyfair();
	void choiceFuncOfFileAffine();
	void choiceFuncOfFilePleyfair();

	void choiceFuncOfText();
	void choiceFuncOfFile();

	void choiceKeyGen();

	int showTextOperations();
	int showFileOperations();
	string checkText();
	string existFile(const string& operation);
	string accessCreateDirForSaveFile(const string& operation, const string& dir);

	uint64_t checkKeyAffine();
	void enterTextToEncryptAffine(uint64_t a, uint64_t b, int mod);
	void enterTextToDecryptAffine(uint64_t a, uint64_t b, int mod);
	void enterFileToEncryptAffine(uint64_t a, uint64_t b, int mod);
	void enterFileToDecryptAffine(uint64_t a, uint64_t b, int mod);

	string checkKeyPleyfair();
	unsigned char checkMarkerPleyfair();
	void enterTextToEncryptPleyfair(const string& key, unsigned char marker, int mod);
	void enterTextToDecryptPleyfair(const string& key, unsigned char marker, int mod);
	void enterFileToEncryptPleyfair(const string& key, unsigned char marker, int mod);
	void enterFileToDecryptPleyfair(const string& key, unsigned char marker, int mod);
};
#endif