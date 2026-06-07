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
	PLAYFAIR
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

int getChoice(int min, int max, const string& prompt);

class Windows {

public:
	void showMenu();
	
private:
	void choiceFuncOfTextAffine();
	void choiceFuncOfTextPleyfair();
	void choiceFuncOfFileAffine();
	void choiceFuncOfFilePleyfair();

	void choiceFuncOfText();
	void choiceFuncOfFile();

	void choiceKeyGen();
};
#endif