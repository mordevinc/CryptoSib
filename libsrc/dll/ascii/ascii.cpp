#include "ascii.h"

unsigned char encrAsciiByte(int shift, unsigned char x) {
    return (unsigned char)((x + shift) % 256);
}

unsigned char decrAsciiByte(int shift, unsigned char y) {
    return (unsigned char)((y - shift + 256) % 256);
}

string encrAsciiText(const string& text, int shift) {
    string result;
    for (unsigned char c : text) {
        result.push_back(encrAsciiByte(shift, c));
    }
    return result;
}

string decrAsciiText(const string& text, int shift) {
    string result;
    for (unsigned char c : text) {
        result.push_back(decrAsciiByte(shift, c));
    }
    return result;
}

bool encrAsciiFile(const string& input, const string& output, int shift) {
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
            out.put(encrAsciiByte(shift, (unsigned char)byte));
        }
        return true;
    }
    catch (...) { return false; }
}

bool decrAsciiFile(const string& input, const string& output, int shift) {
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
            out.put(decrAsciiByte(shift, (unsigned char)byte));
        }
        return true;
    }
    catch (...) { return false; }
}