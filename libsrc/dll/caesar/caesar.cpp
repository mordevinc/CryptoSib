#include "caesar.h"

unsigned char encrCaesarByte(int shift, int m, unsigned char x) {
    return (unsigned char)((x + shift) % m);
}

unsigned char decrCaesarByte(int shift, int m, unsigned char y) {
    return (unsigned char)((y - shift + m) % m);
}

string encrCaesarText(const string& text, int shift, int m) {
    string result;
    for (unsigned char c : text) {
        result.push_back(encrCaesarByte(shift, m, c));
    }
    return result;
}

string decrCaesarText(const string& text, int shift, int m) {
    string result;
    for (unsigned char c : text) {
        result.push_back(decrCaesarByte(shift, m, c));
    }
    return result;
}

bool encrCaesarFile(const string& input, const string& output, int shift, int m) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        char byte;
        while (in.get(byte)) {
            out.put(encrCaesarByte(shift, m, (unsigned char)byte));
        }
        return true;
    }
    catch (...) { return false; }
}

bool decrCaesarFile(const string& input, const string& output, int shift, int m) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        char byte;
        while (in.get(byte)) {
            out.put(decrCaesarByte(shift, m, (unsigned char)byte));
        }
        return true;
    }
    catch (...) { return false; }
}