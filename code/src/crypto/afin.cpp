#include "crypto.h"

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