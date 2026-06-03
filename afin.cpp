#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <iomanip>

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
unsigned char** genMatrixPleyf(string key) {
	unsigned char** mp;
	mp = new unsigned char*[16];
	for (int i = 0; i < 16; ++i) {
		mp[i] = new unsigned char[16];
	}
	unordered_set<unsigned char> used;
	int i = 0;
	int j = 0;
	for (unsigned char item : key) {
		if (used.find(item) == used.end()) {
			mp[i][j] = item;
			used.insert(item);
			++j;
			if (j == 16) {
				j = 0;
				++i;
			}
			if (i == 16) return mp;
		}
	}
	for (unsigned char symb = 0; symb < 255; ++symb) {
		if (used.find(symb) == used.end()) {
			mp[i][j] = symb;
			used.insert(symb);
			++j;
			if (j == 16) {
				j = 0;
				++i;
			}
		}
	}
	if (used.find(255) == used.end()) mp[i][j] = 255;
	return mp;
}
void deleteMatrix(unsigned char** matrix) {
	for (int i = 0; i < 16; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
vector<string> genBigrams(string text, unsigned char marker) {
	vector<string> bigrams;
	string bg;
	for (int i = 0; i < text.size(); ++i) {
		if (i + 1 >= text.size() || text[i] == text[i + 1]) {
			bg.push_back(text[i]);
			bg.push_back(marker);
			bigrams.push_back(bg);
			bg.clear();				
			text.erase(i, 1);
			--i;
		}
		else {
			bg.push_back(text[i]);
			bg.push_back(text[i+1]);
			bigrams.push_back(bg);
			bg.clear();
			text.erase(i, 2);
			if (i == 0) --i;
			else i -= 2;
		}
	}
	return bigrams;
}

pair<int, int> findCoordSymb(unsigned char** pm, unsigned char symb) {
	pair<int, int> coord;
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 16; j++) {
			if (pm[i][j] == symb) {
				coord = { i, j };
				return coord;
			}
		}
	}
	return { -1, -1 };
}
unsigned char findSymbForCoord(unsigned char** pm, pair<int, int> coord) {
	unsigned char symb;
	if (coord.first < 16 && coord.second < 16) {
		symb = pm[coord.first][coord.second];
		return symb;
	}
	return 0;
}

vector<string> encrBigrams(unsigned char** pm, vector<string> bigrams) {
	vector<string> encrBigrams;
	string encrBigram;
	for(string item : bigrams){
		unsigned char symb0 = item[0];
		unsigned char symb1 = item[1];
		pair<int, int> coordSymb0 = findCoordSymb(pm, symb0);
		pair<int, int> coordSymb1 = findCoordSymb(pm, symb1);
		if (coordSymb0.first == coordSymb1.first) {
			coordSymb0.second = (coordSymb0.second + 1) % 16;
			coordSymb1.second = (coordSymb1.second + 1) % 16;
		}
		else if (coordSymb0.second == coordSymb1.second) {
			coordSymb0.first = (coordSymb0.first + 1) % 16;
			coordSymb1.first = (coordSymb1.first + 1) % 16;
		}
		else {
			int temp = coordSymb0.second;
			coordSymb0.second = coordSymb1.second;
			coordSymb1.second = temp;
		}
		symb0 = findSymbForCoord(pm, coordSymb0);
		symb1 = findSymbForCoord(pm, coordSymb1);
		encrBigram.push_back(symb0);
		encrBigram.push_back(symb1);
		encrBigrams.push_back(encrBigram);
		encrBigram.clear();
	}
	return encrBigrams;
}

string encrText(vector<string> encrBigrams) {
	string text;
	for (string item : encrBigrams) {
		text.append(item);
	}
	return text;
}

vector<string> genEncrBigrams(string encrText, unsigned char marker) {
	vector<string> encrBigrams = genBigrams(encrText, marker);
	return encrBigrams;
}

vector<string> decrBigrams(unsigned char** pm, vector<string>EncrBigrams) {
	vector<string> decrBigrams;
	string decrBigram;
	for (string item : EncrBigrams) {
		unsigned char symb0 = item[0];
		unsigned char symb1 = item[1];
		pair<int, int> coordSymb0 = findCoordSymb(pm, symb0);
		pair<int, int> coordSymb1 = findCoordSymb(pm, symb1);
		if (coordSymb0.first == coordSymb1.first) {
			coordSymb0.second = (coordSymb0.second - 1 + 16) % 16;
			coordSymb1.second = (coordSymb1.second - 1 + 16) % 16;
		}
		else if (coordSymb0.second == coordSymb1.second) {
			coordSymb0.first = (coordSymb0.first - 1 + 16) % 16;
			coordSymb1.first = (coordSymb1.first - 1 + 16) % 16;
		}
		else {
			int temp = coordSymb0.second;
			coordSymb0.second = coordSymb1.second;
			coordSymb1.second = temp;
		}
		symb0 = findSymbForCoord(pm, coordSymb0);
		symb1 = findSymbForCoord(pm, coordSymb1);
		decrBigram.push_back(symb0);
		decrBigram.push_back(symb1);
		decrBigrams.push_back(decrBigram);
		decrBigram.clear();
	}
	return decrBigrams;
}

string decrText(vector<string> decrBigrams, unsigned char marker) {
	string text;
	for (string item : decrBigrams) {
		for (unsigned char symb : item) {
			if (symb != marker) text.push_back(symb);
		}
	}
	return text;
}
void Pleyf(string key, string text, unsigned char marker) {
	unsigned char** pm = genMatrixPleyf(key);
	vector<string> bgr = genBigrams(text, marker);
	vector<string> encrBgr = encrBigrams(pm, bgr);
	string encrTxt = encrText(encrBgr);
	cout << encrTxt << endl;
	vector<string> genEncrBgr = genEncrBigrams(encrTxt, marker);
	vector<string> decrBgr = decrBigrams(pm, genEncrBgr);
	string decrTxt = decrText(decrBgr, marker);
	cout << decrTxt << endl;
}


// Преобразуем бинарный файл в HEX строку
string fileToHex(const string& filename) {
	ifstream in(filename, ios::binary);
	string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	in.close();

	ostringstream oss;
	oss << hex << setfill('0');
	for (unsigned char c : data) {
		oss << setw(2) << (int)c;
	}
	return oss.str();
}

// Преобразуем HEX строку обратно в бинарный файл 
void hexToFile(const string& hex, const string& filename) {
	ofstream out(filename, ios::binary);
	for (size_t i = 0; i < hex.size(); i += 2) {
		char byte = (char)stoi(hex.substr(i, 2), nullptr, 16);
		out.put(byte);
	}
	out.close();
}


bool encrPleyfFile(const string& input, const string& output, string key, unsigned char marker) {
	string hex = fileToHex(input);

	unsigned char** pm = genMatrixPleyf(key);
	vector<string> bgr = genBigrams(hex, marker);
	vector<string> encrBgr = encrBigrams(pm, bgr);
	string encr = encrText(encrBgr);

	ofstream out(output, ios::binary);
	out.write(encr.c_str(), encr.size());
	out.close();
	deleteMatrix(pm);
	return true;
}


bool decrPleyfFile(const string& input, const string& output, string key, unsigned char marker) {
	unsigned char** pm = genMatrixPleyf(key);
	ifstream in(input, ios::binary);
	string encrData((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	in.close();

	vector<string> encrBgr = genEncrBigrams(encrData, marker);
	vector<string> decrBgr = decrBigrams(pm, encrBgr);
	string decrHex = decrText(decrBgr, marker);


	hexToFile(decrHex, output);

	deleteMatrix(pm);
	return true;
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
	getline(cin, textPl);
	cin >> marker;
	//Pleyf(keyPl, textPl, marker);
	encrPleyfFile("1.png", "2.txt", keyPl, marker);
	decrPleyfFile("2.txt", "3.png", keyPl, marker);
	return 0;
}