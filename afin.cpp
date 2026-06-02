#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

using namespace std;

int evk(int base, int mod) {
	int a = base;
	int b = mod;
	int oldB = 0;
	while (b > 0) {
		oldB = b;
		b = a % b;
		a = oldB;
	}
	return a;
}

int ObrEvk(int a, int b, char ret) {
	int oldU = 1;
	int oldV = 0;
	int u = 0;
	int v = 1;
	int d = 0;
	int q = 0;
	int r = 0;
	int c = a;
	int m = b;
	int tempU = 0;
	int tempV = 0;
	do {
		r = c % m;
		q = c / m;
		c = m;
		m = r;
		if (r <= 0) break;
		tempU = u;
		tempV = v;
		u = oldU - (q * tempU);
		v = oldV - (q * tempV);
		oldU = tempU;
		oldV = tempV;
	} while (r > 0);
	if (u < 0) u += b;
	if (ret == 'u') return u;
	if (ret == 'r') return c;
	if (ret == 'v') return v;
	return 0;
}

unsigned char encrAfinByte(int a, int b, int m, unsigned char x) {
	int E = (a * x + b) % m;
	return E;
}

unsigned char decrAfinByte(int d, int b, int m, unsigned char y) {
	int D = (d * (y - b + m) % m) % m;
	return D;
}

bool isProstAM(int a, int m) {
	if (evk(a, m) == 1) return 1;
	return 0;
}
bool encrAfinFile(const string& input, const string& output, int a, int b, int m) {
	ifstream in(input, ios::binary);
	ofstream out(output, ios::binary);
	if (!in || !out) return false;
	char byte;
	while (in.get(byte)) {
		out.put(encrAfinByte(a, b, m, (unsigned char)byte));
	}
	in.close();
	out.close();
	return 1;
}
bool decrAfinFile(const string& input, const string& output, int d, int b, int m) {
	ifstream in(input, ios::binary);
	ofstream out(output, ios::binary);
	if (!in || !out) return false;
	char byte;
	while (in.get(byte)) {
		out.put(decrAfinByte(d, b, m, (unsigned char)byte));
	}
	in.close();
	out.close();
	return 1;
}

int main() {
	SetConsoleOutputCP(1251);  
	SetConsoleCP(1251);
	int a = 7;
	int b = 13;
	int m = 256;
	int d = ObrEvk(a, m, 'u');
	unsigned char x = 'Д';
	string text = "Проверка";
	vector<unsigned char> enc;
	vector<unsigned char> dec;

	// Шифрование
	for (unsigned char item : text) {
		enc.push_back(encrAfinByte(a, b, m, item));
	}

	// Расшифрование
	for (unsigned char item : enc) {
		dec.push_back(decrAfinByte(ObrEvk(a, m, 'u'), b, m, item));
	}

	// Вывод исходной строки
	cout << "Исходная: " << text << endl;

	// Вывод зашифрованной строки (как символы)
	cout << "Зашифрованная: ";
	for (unsigned char item : enc) {
		cout << item;
	}
	cout << endl << d << endl;

	// Вывод расшифрованной строки
	cout << "Расшифрованная: ";
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
	encrAfinFile("1.png", "2.txt", a, b, m);
	decrAfinFile("2.txt", "3.png", d, b, m);
	return 0;
}