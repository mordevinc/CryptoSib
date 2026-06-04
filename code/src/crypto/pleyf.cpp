#include "crypto.h"

unsigned char** genMatrixPleyf(string key) {
	unsigned char** mp;
	mp = new unsigned char* [16];
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
			bg.push_back(text[i + 1]);
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
	for (string item : bigrams) {
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
	deleteMatrix(pm);
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
