#include "permut.h"

string encrPermutationText(const string& text, const vector<int>& key) {
    int cols = key.size();
    int rows = (text.size() + cols - 1) / cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    for (int i = 0; i < text.size(); i++) {
        matrix[i / cols][i % cols] = text[i];
    }

    string result;
    for (int k : key) {
        for (int row = 0; row < rows; row++) {
            if (matrix[row][k] != ' ') {
                result.push_back(matrix[row][k]);
            }
        }
    }
    return result;
}

string decrPermutationText(const string& text, const vector<int>& key) {
    int cols = key.size();
    int rows = (text.size() + cols - 1) / cols;
    vector<vector<char>> matrix(rows, vector<char>(cols, ' '));

    vector<int> invKey(cols);
    for (int i = 0; i < cols; i++) {
        invKey[key[i]] = i;
    }

    int idx = 0;
    for (int k : key) {
        for (int row = 0; row < rows; row++) {
            if (idx < text.size() && row * cols + k < rows * cols) {
                matrix[row][k] = text[idx++];
            }
        }
    }

    string result;
    for (int i = 0; i < rows * cols && i < text.size(); i++) {
        if (matrix[i / cols][i % cols] != ' ') {
            result.push_back(matrix[i / cols][i % cols]);
        }
    }
    return result;
}

bool encrPermutationFile(const string& input, const string& output, const vector<int>& key) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string encrypted = encrPermutationText(data, key);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(encrypted.c_str(), encrypted.size());
        return true;
    }
    catch (...) { return false; }
}

bool decrPermutationFile(const string& input, const string& output, const vector<int>& key) {
    try {
        fs::path outPath(output);
        if (!outPath.parent_path().empty()) {
            if (!fs::exists(outPath.parent_path())) {
                fs::create_directories(outPath.parent_path());
            }
        }
        ifstream in(input, ios::binary);
        if (!in.is_open()) return false;
        string data((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
        in.close();
        string decrypted = decrPermutationText(data, key);
        ofstream out(output, ios::binary);
        if (!out.is_open()) return false;
        out.write(decrypted.c_str(), decrypted.size());
        return true;
    }
    catch (...) { return false; }
}