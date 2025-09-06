#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

string input();
string* token_array_init();
void to_lower_letter(string& token);
bool is_separator(char c);
string* tokenize(string line, size_t& token_count);
void output_tokens(string* token_array, size_t& token_count);


string input() {
    string line;
    getline(cin, line);
    return line;
}

string* token_array_init() {
    const int maxInstructionCount = 256; 
    string* tokenArray = new string[maxInstructionCount*4+1]; // max size instr = 4, +1 for last char ' ' ===> n*4+1
    return tokenArray;
}

void to_lower_letter(string& token) {
    transform(token.begin(), token.end(), token.begin(), ::tolower);
}

bool is_separator(char c) {
    unordered_set<char> separatorsTypes = { ' ', ',' };
    return separatorsTypes.find(c) != separatorsTypes.end();
}

string* tokenize(string line, size_t& token_count) {
    string* token_array = token_array_init();
    size_t i = 0;
    token_count = 0;
    string token;
    while (i < line.size()) {
        if (is_separator(line[i])) { 
            to_lower_letter(token);
            token_array[token_count++] = token;
            token.clear();

        }
        else {
            token.push_back(line[i]);
        }
        i++;
    }
    token_array[token_count++] = token; // необходимо для строки, незаконченной пробелом
    token.clear();
    return token_array;
}

void output_tokens(string* token_array, size_t& token_count) {
    cout << token_count << endl;
    cout << "<";
    for (size_t i = 0; i < token_count; ++i) {
        cout << "> " << token_array[i] << " <";
    }
    cout << ">";
    cout << endl;
}