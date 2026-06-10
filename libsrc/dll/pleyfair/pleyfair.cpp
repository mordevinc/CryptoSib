#include "pleyfair.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <stdexcept>



unsigned char** genMatrixPleyfair(string key, int mod) {
    try {
        int m = sqrtZ(mod);
        unsigned char** mp;
        mp = new unsigned char* [m];
        for (int i = 0; i < m; ++i) {
            mp[i] = new unsigned char[m];
        }
        unordered_set<unsigned char> used;
        int i = 0;
        int j = 0;
        for (unsigned char item : key) {
            if (used.find(item) == used.end()) {
                mp[i][j] = item;
                used.insert(item);
                ++j;
                if (j == m) {
                    j = 0;
                    ++i;
                }
                if (i == m) return mp;
            }
        }
        for (unsigned char symb = 0; symb < mod - 1; ++symb) {
            if (used.find(symb) == used.end()) {
                mp[i][j] = symb;
                used.insert(symb);
                ++j;
                if (j == m) {
                    j = 0;
                    ++i;
                }
            }
        }
        if (used.find(mod - 1) == used.end()) mp[i][j] = mod - 1;
        return mp;
    }
    catch (const bad_alloc& e) {
        cerr << "Ошибка: недостаточно памяти для создания матрицы" << endl;
        return nullptr;
    }
}

void deleteMatrix(unsigned char** matrix, int mod) {
    int m = sqrtZ(mod);
    for (int i = 0; i < m; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

vector<string> genBigramsPleyfair(string text, unsigned char marker) {
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

pair<int, int> findCoordSymbPleyfair(unsigned char** pm, unsigned char symb, int mod) {
    int m = sqrtZ(mod);
    pair<int, int> coord;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < m; j++) {
            if (pm[i][j] == symb) {
                coord = { i, j };
                return coord;
            }
        }
    }
    return { -1, -1 };
}

unsigned char findSymbForCoordPleyfair(unsigned char** pm, pair<int, int> coord, int mod) {
    int m = sqrtZ(mod);
    unsigned char symb;
    if (coord.first < m && coord.second < m) {
        symb = pm[coord.first][coord.second];
        return symb;
    }
    return 0;
}

vector<string> encrBigramsPleyfair(unsigned char** pm, vector<string> bigrams, int mod) {
    int m = sqrtZ(mod);
    vector<string> encrBigramsPleyfair;
    string encrBigram;
    for (string item : bigrams) {
        unsigned char symb0 = item[0];
        unsigned char symb1 = item[1];
        pair<int, int> coordSymb0 = findCoordSymbPleyfair(pm, symb0, mod);
        pair<int, int> coordSymb1 = findCoordSymbPleyfair(pm, symb1, mod);
        if (coordSymb0.first == coordSymb1.first) {
            coordSymb0.second = (coordSymb0.second + 1) % m;
            coordSymb1.second = (coordSymb1.second + 1) % m;
        }
        else if (coordSymb0.second == coordSymb1.second) {
            coordSymb0.first = (coordSymb0.first + 1) % m;
            coordSymb1.first = (coordSymb1.first + 1) % m;
        }
        else {
            int temp = coordSymb0.second;
            coordSymb0.second = coordSymb1.second;
            coordSymb1.second = temp;
        }
        symb0 = findSymbForCoordPleyfair(pm, coordSymb0, mod);
        symb1 = findSymbForCoordPleyfair(pm, coordSymb1, mod);
        encrBigram.push_back(symb0);
        encrBigram.push_back(symb1);
        encrBigramsPleyfair.push_back(encrBigram);
        encrBigram.clear();
    }
    return encrBigramsPleyfair;
}

string encrTextPleyfair(vector<string> encrBigramsPleyfair) {
    string text;
    for (string item : encrBigramsPleyfair) {
        text.append(item);
    }
    return text;
}

vector<string> genEncrBigramsPleyfair(string encrTextPleyfair, unsigned char marker) {
    vector<string> encrBigramsPleyfair = genBigramsPleyfair(encrTextPleyfair, marker);
    return encrBigramsPleyfair;
}

vector<string> decrBigramsPleyfair(unsigned char** pm, vector<string> encrBigramsPleyfair, int mod) {
    int m = sqrtZ(mod);
    vector<string> decrBigramsPleyfair;
    string decrBigram;
    for (string item : encrBigramsPleyfair) {
        unsigned char symb0 = item[0];
        unsigned char symb1 = item[1];
        pair<int, int> coordSymb0 = findCoordSymbPleyfair(pm, symb0, mod);
        pair<int, int> coordSymb1 = findCoordSymbPleyfair(pm, symb1, mod);
        if (coordSymb0.first == coordSymb1.first) {
            coordSymb0.second = (coordSymb0.second - 1 + m) % m;
            coordSymb1.second = (coordSymb1.second - 1 + m) % m;
        }
        else if (coordSymb0.second == coordSymb1.second) {
            coordSymb0.first = (coordSymb0.first - 1 + m) % m;
            coordSymb1.first = (coordSymb1.first - 1 + m) % m;
        }
        else {
            int temp = coordSymb0.second;
            coordSymb0.second = coordSymb1.second;
            coordSymb1.second = temp;
        }
        symb0 = findSymbForCoordPleyfair(pm, coordSymb0, mod);
        symb1 = findSymbForCoordPleyfair(pm, coordSymb1, mod);
        decrBigram.push_back(symb0);
        decrBigram.push_back(symb1);
        decrBigramsPleyfair.push_back(decrBigram);
        decrBigram.clear();
    }
    return decrBigramsPleyfair;
}

string decrTextPleyfair(vector<string> decrBigramsPleyfair, unsigned char marker) {
    string text;
    for (string item : decrBigramsPleyfair) {
        for (unsigned char symb : item) {
            if (symb != marker) text.push_back(symb);
        }
    }
    return text;
}

void Pleyf(string key, string text, unsigned char marker, int mod) {
    unsigned char** pm = genMatrixPleyfair(key, mod);
    vector<string> bgr = genBigramsPleyfair(text, marker);
    vector<string> encrBgr = encrBigramsPleyfair(pm, bgr, mod);
    string encrTxt = encrTextPleyfair(encrBgr);
    cout << encrTxt << endl;
    vector<string> genEncrBgr = genEncrBigramsPleyfair(encrTxt, marker);
    vector<string> decrBgr = decrBigramsPleyfair(pm, genEncrBgr, mod);
    deleteMatrix(pm, mod);
    string decrTxt = decrTextPleyfair(decrBgr, marker);
    cout << decrTxt << endl;
}

// Преобразуем бинарный файл в HEX строку
string fileToHex(const string& filename) {
    try {
        ifstream in(filename, ios::binary);
        if (!in) throw runtime_error("Не удалось открыть файл: " + filename);
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();

        ostringstream oss;
        oss << hex << setfill('0');
        for (unsigned char c : data) {
            oss << setw(2) << (int)c;
        }
        return oss.str();
    }
    catch (const exception& e) {
        cerr << "Ошибка при чтении файла: " << e.what() << endl;
        throw;
    }
}

// Преобразуем HEX строку обратно в бинарный файл 
void hexToFile(const string& hex, const string& filename) {
    try {
        ofstream out(filename, ios::binary);
        if (!out) throw runtime_error("Не удалось создать файл: " + filename);
        for (size_t i = 0; i < hex.size(); i += 2) {
            if (i + 1 >= hex.size()) {
                throw runtime_error("Некорректная HEX строка");
            }
            char byte = (char)stoi(hex.substr(i, 2), nullptr, 16);
            out.put(byte);
        }
        out.close();
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: неверный HEX символ" << endl;
        throw;
    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: HEX значение вне диапазона" << endl;
        throw;
    }
}

bool encrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod) {
    try {
        string hex = fileToHex(input);
        if (hex.empty()) throw runtime_error("Файл пуст или не прочитан");
        unsigned char** pm = genMatrixPleyfair(key, mod);
        if (!pm) throw runtime_error("Не удалось создать матрицу");
        vector<string> bgr = genBigramsPleyfair(hex, marker);
        vector<string> encrBgr = encrBigramsPleyfair(pm, bgr, mod);
        string encr = encrTextPleyfair(encrBgr);

        ofstream out(output, ios::binary);
        if (!out) throw runtime_error("Не удалось создать выходной файл: " + output);
        out.write(encr.c_str(), encr.size());
        out.close();
        deleteMatrix(pm, mod);
        return true;
    }
    catch (const exception& e) {
        cerr << "Ошибка при шифровании файла: " << e.what() << endl;
        return false;
    }
}

bool decrFilePleyfair(const string& input, const string& output, string key, unsigned char marker, int mod) {
    try {
        unsigned char** pm = genMatrixPleyfair(key, mod);
        if (!pm) throw runtime_error("Не удалось создать матрицу");
        ifstream in(input, ios::binary);
        if (!in) throw runtime_error("Не удалось открыть файл: " + input);
        string encrData((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();

        vector<string> encrBgr = genEncrBigramsPleyfair(encrData, marker);
        vector<string> decrBgr = decrBigramsPleyfair(pm, encrBgr, mod);
        string decrHex = decrTextPleyfair(decrBgr, marker);

        hexToFile(decrHex, output);

        deleteMatrix(pm, mod);
        return true;
    }
    catch (const exception& e) {
        cerr << "Ошибка при дешифровании файла: " << e.what() << endl;
        return false;
    }
}