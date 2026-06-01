#include <iostream>
#include <locale>
#include <string>
#include <vector>

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

int ObrEvk(int a, int b) {
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
	return u;
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


int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");
	int a = 7;
	int b = 13;
	int m = 255;
	unsigned char x = 'Д';
	string text = "Проверка";
	vector<unsigned char> enc;
	vector<unsigned char> dec;
	for (unsigned char item : text) {
		enc.push_back(encrAfinByte(a, b, m, item));
	}
	cout << endl;
	for (unsigned char item : enc) {
		dec.push_back(decrAfinByte(ObrEvk(a, m), b, m, item));
	}
	for (unsigned char item : enc) {
		cout << item;
	}
	for (unsigned char item : dec) {
		cout << item;
	}
	if (isProstAM(a, m)) {
		unsigned char y = encrAfinByte(a, b, m, x);
		cout << x << endl;
		cout << y << endl;
		cout << decrAfinByte(ObrEvk(a, m), b, m, y);
	}
	return 0;
}