#include "../menu.h"

string Windows::checkKeyPleyfair() {
	string key;
	while (true) {
		cout << "Введите ключ" << endl;
		getline(cin, key);
		bool validKey = 1;
		for (unsigned char item : key) {
			if (item < MODULE) {
				continue;
			}
			else {
				cout << "Символы, содержащиеся в ключе не относятся к данному алфавиту" << endl;
				validKey = 0;
				break;
			}
		}
		if (validKey) {
			return key;
		}
	}
}

unsigned char Windows::checkMarkerPleyfair(){
	unsigned char marker;
	while (true) {
		cout << "Введите маркер для склейки биграм" << endl;
		cin >> marker;
		cin.ignore();
		if (marker < MODULE) {
			return marker;
		}
		else {
			cout << "Символ для маркера не относятся к данному алфавиту" << endl;
		}

	}
}

void Windows::enterTextToEncryptPleyfair(const string& key, unsigned char marker, int mod) {
	string text = Windows::checkText();
	unsigned char** pm = genMatrixPleyfair(key, mod);
	if (!pm) throw runtime_error("Не удалось создать матрицу");
	vector<string> bgr = genBigramsPleyfair(text, marker);
	vector<string> encrBgr = encrBigramsPleyfair(pm, bgr, mod);
	deleteMatrix(pm, mod);
	string encrTxt = encrTextPleyfair(encrBgr);
	cout << "Зашифрованный текст:" << endl;
	cout << encrTxt << endl;
}

void Windows::enterTextToDecryptPleyfair(const string& key, unsigned char marker, int mod) {
	string text = Windows::checkText();
	unsigned char** pm = genMatrixPleyfair(key, mod);
	if (!pm) throw runtime_error("Не удалось создать матрицу");
	vector<string> genEncrBgr = genEncrBigramsPleyfair(text, marker);
	vector<string> decrBgr = decrBigramsPleyfair(pm, genEncrBgr, mod);
	deleteMatrix(pm, mod);
	string decrTxt = decrTextPleyfair(decrBgr, marker);
	cout << "Расшифрованный текст:" << endl;
	cout << decrTxt << endl;
}
void Windows::enterFileToEncryptPleyfair(const string& key, unsigned char marker, int mod) {
	string pathFileToEncr = Windows::existFile("зашифровать", INPUT_DIR);
	string pathFileEncr = Windows::accessCreateDirForSaveFile("зашифрованному", ENCR_DIR);

	if (encrFilePleyfair(INPUT_DIR + pathFileToEncr, ENCR_DIR + pathFileEncr, key, marker, mod)) {
		cout << "Файл успешно зашифрован!" << endl;
		cout << "Зашифрованный файл находится по пути: " << ENCR_DIR + pathFileEncr << endl;
	}
	else {
		cout << "Ошибка при шифровании файла!" << endl;
	}
}
void Windows::enterFileToDecryptPleyfair(const string& key, unsigned char marker, int mod) {
	string pathFileToDecr = Windows::existFile("расшифровать", ENCR_DIR);
	string pathFileDecr = Windows::accessCreateDirForSaveFile("расшифрованному", DECR_DIR);

	if (decrFilePleyfair(ENCR_DIR + pathFileToDecr, DECR_DIR + pathFileDecr, key, marker, mod)) {
		cout << "Файл успешно расшифрован!" << endl;
		cout << "Расшифрованный файл находится по пути: " << DECR_DIR + pathFileDecr << endl;
	}
	else {
		cout << "Ошибка при расшифровании файла!" << endl;
	}
}



void Windows::choiceFuncOfTextPleyfair() {
	try {
		string key = Windows::checkKeyPleyfair();
		unsigned char marker = Windows::checkMarkerPleyfair();

		int choice = Windows::showTextOperations();

		switch (FunctionsOfText(choice)) {
		case FunctionsOfText::ENCRYPT_TEXT: {
			Windows::enterTextToEncryptPleyfair(key, marker, MODULE);
			break;
		}
		case FunctionsOfText::DECRYPT_TEXT: {
			Windows::enterTextToDecryptPleyfair(key, marker, MODULE);
			break;
		}
		default: cout << "ОШИБКА" << endl;
		}
	}
	catch (const bad_alloc& e) {
		cerr << "Ошибка выделения памяти: " << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}

void Windows::choiceFuncOfFilePleyfair() {
	try {
		string key = Windows::checkKeyPleyfair();
		unsigned char marker = Windows::checkMarkerPleyfair();

		int choice = Windows::showFileOperations();

		switch (FunctionsOfFile(choice)) {
		case FunctionsOfFile::ENCRYPT_FILE: {
			Windows::enterFileToEncryptPleyfair(key, marker, MODULE);
			break;
		}
		case FunctionsOfFile::DECRYPT_FILE: {
			Windows::enterFileToDecryptPleyfair(key, marker, MODULE);
			break;
		}
		default: cout << "ОШИБКА" << endl;
		}
	}
	catch (const fs::filesystem_error& e) {
		cerr << "Ошибка файловой системы: " << e.what() << endl;
	}
	catch (const bad_alloc& e) {
		cerr << "Ошибка выделения памяти: " << e.what() << endl;
	}
	catch (const exception& e) {
		cerr << "Ошибка: " << e.what() << endl;
	}
}