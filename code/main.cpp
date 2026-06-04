#include "src/crypto/crypto.h"
// Платформозависимые заголовки
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 
#define NOGDI                
#include <windows.h>
#pragma comment(lib, "src/dll/mathFunction.lib")
#endif
#define INPUT_DIR   "files/input/"
#define ENCR_DIR  "files/encryption/"
#define DECR_DIR  "files/decryption/"


// Установка кодировки консоли
void setConsoleEncoding() {
#ifdef _WIN32
	// Windows: устанавливаем кодировку 1251
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
#endif
}
int main() {
	setConsoleEncoding();
	int a = 7;
	int b = 13;
	int m = 256;
	int d = ObrEvk(a, m, 'u');
	unsigned char x = 'Д';
	string text = "Проверка";
	vector<unsigned char> enc;
	vector<unsigned char> dec;
	getline(cin, text);
	// Шифрование
	for (unsigned char item : text) {
		enc.push_back(encrAfinByte(a, b, m, item));
	}

	// Расшифрование
	for (unsigned char item : enc) {
		dec.push_back(decrAfinByte(ObrEvk(a, m, 'u'), b, m, item));
	}

	// Вывод исходной строки
	cout << "Original: " << text << endl;

	// Вывод зашифрованной строки (как символы)
	cout << "Encryption: ";
	for (unsigned char item : enc) {
		cout << item;
	}
	cout << endl << d << endl;

	// Вывод расшифрованной строки
	cout << "Decryption: ";
	for (unsigned char item : dec) {
		cout << item;
	}
	cout << endl;

	if (isProstAM(a, m)) {
		unsigned char y = encrAfinByte(a, b, m, x);
		cout << x << endl;
		cout << y << endl;
		cout << decrAfinByte(d, b, m, y);
	}
	//encrAfinFile("1.png", "2.txt", a, b, m);
	//decrAfinFile("2.txt", "3.png", d, b, m);
	cout << endl;
	/*unsigned char** pm = genMatrixPleyf("мойkey2565");
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 16; ++j) {
			cout << pm[i][j];
		}
		cout << endl;
	}*/
	string keyPl;
	string textPl;
	unsigned char marker;
	getline(cin, keyPl);
	//getline(cin, textPl);
	string inputF;
	string encrF;
	string decrF;
	cin >> marker >> inputF >> encrF >> decrF;
	//Pleyf(keyPl, textPl, marker);
	encrPleyfFile(INPUT_DIR+inputF, ENCR_DIR+encrF, keyPl, marker);
	decrPleyfFile(ENCR_DIR+encrF, DECR_DIR+decrF, keyPl, marker);
	return 0;
}