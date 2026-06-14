#include "../menu.h"

uint64_t Windows::checkKeyAffine() {
	cout << "Введите ключ 'a'" << endl;
	uint64_t a;
	while (true) {
		cin >> a;
		if (isPrimeAM(a, MODULE)) {
			return a;

		}
		else {
			cout << "Числа a и m не являются взаимно простыми! Попробуйте снова!" << endl;
		}
	}
}

void Windows::enterTextToEncryptAffine(uint64_t a, uint64_t b, int mod) {
	cout << "Введите текст для шифрования" << endl;
	string text = Windows::checkText();
	cout << "Зашифрованный текст: " << endl;
	cout << encrAffineText(text, a, b, mod) << endl;
}
void Windows::enterTextToDecryptAffine(uint64_t a, uint64_t b, int mod) {
	cout << "Введите текст для расшифрования" << endl;
	string text = Windows::checkText();
	cout << "Расшифрованный текст: " << endl;
	cout << decrAffineText(text, a, b, MODULE) << endl;
}
void Windows::enterFileToEncryptAffine(uint64_t a, uint64_t b, int mod) {
	string pathFileToEncr = Windows::existFile("зашифровать", INPUT_DIR);
	string pathFileEncr = Windows::accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);
	if (encrAffineFile(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, a, b, MODULE)) {
		cout << "Файл успешно зашифрован!" << endl;
		cout << "Зашифрованный файл находится по пути: " << ENCR_DIR + pathFileEncr << endl;
	}
	else {
		cout << "Ошибка при шифровании файла!" << endl;
	}
}
void Windows::enterFileToDecryptAffine(uint64_t a, uint64_t b, int mod) {
	string pathFileToDecr = Windows::existFile("расшифровать", ENCR_DIR);
	string pathFileDecr = Windows::accessCreateDirForSaveFile("расшифрованному", DECR_DIR);

	if (decrAffineFile(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, a, b, MODULE)) {
		cout << "Файл успешно расшифрован!" << endl;
		cout << "Расшифрованный файл находится по пути: " << DECR_DIR + pathFileDecr << endl;
	}
	else {
		cout << "Ошибка при расшифровании файла!" << endl;
	}
}



void Windows::choiceFuncOfTextAffine() {
	try {
		uint64_t a = checkKeyAffine();
		cout << "Введите ключ 'b'" << endl;
		uint64_t b;
		cin >> b;
		cin.ignore();
		int choice = Windows::showTextOperations();
		switch (FunctionsOfText(choice)) {
		case FunctionsOfText::ENCRYPT_TEXT: {
			Windows::enterTextToEncryptAffine(a, b, MODULE);
			break;
		}
		case FunctionsOfText::DECRYPT_TEXT: {
			Windows::enterTextToDecryptAffine(a, b, MODULE);
			break;
		}
		default: cout << "ОШИБКА" << endl;
		}
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}

void Windows::choiceFuncOfFileAffine() {
	try {
		uint64_t a = Windows::checkKeyAffine();
		cout << "Введите ключ 'b'" << endl;
		uint64_t b;
		cin >> b;
		cin.ignore();

		int choice = Windows::showFileOperations();

		switch (FunctionsOfFile(choice)) {
		case FunctionsOfFile::ENCRYPT_FILE: {
			Windows::enterFileToEncryptAffine(a, b, MODULE);
			break;
		}
		case FunctionsOfFile::DECRYPT_FILE: {
			Windows::enterFileToDecryptAffine(a, b, MODULE);
			break;
		}
		default: cout << "ERROR" << endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		cerr << "Ошибка файловой системы: " << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}