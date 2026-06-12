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
#pragma comment(lib, "src/dll/caesar.lib")
#pragma comment(lib, "src/dll/rsa.lib")
#pragma comment(lib, "src/dll/ascii.lib")
#pragma comment(lib, "src/dll/idea.lib")
#pragma comment(lib, "src/dll/rc4.lib")
#pragma comment(lib, "src/dll/permut.lib")
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
	CAESAR,
	RSA,
	ASCII,
	IDEA,
	RC4,
	PERMUTATION
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
	string existFile(const string& operation, const string& dir);
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

	// IDEA
	string checkKeyIdea();
	void enterTextToEncryptIdea(const string& password);
	void enterTextToDecryptIdea(const string& password);
	void enterFileToEncryptIdea(const string& password);
	void enterFileToDecryptIdea(const string& password);
	void choiceFuncOfTextIdea();
	void choiceFuncOfFileIdea();

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
	void choiceKeyGenIdea();
	void choiceKeyGenRc4();
	void choiceKeyGenPermutation();
};
#endif