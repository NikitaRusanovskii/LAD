#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

string input() {
    string line;
    getline(cin, line);
    return line;
}

string* token_array_init() {
    const int max_instruction_amount = 15; 
    string* tokens_array = new string[max_instruction_amount*4+1]; // max size instr = 4, +1 for last char ' ' ===> n*4+1
    return tokens_array;
}

bool is_separator(char c) {
    unordered_set<char> types_seps = { ' ', ',' };
    return types_seps.find(c) != types_seps.end();
}

string* tokenize(string line, size_t& tc_ptr) {
    string* token_array = token_array_init();
    size_t i = 0;
    tc_ptr = 0;
    string token;
    while (i < line.size()) {
        if (is_separator(line[i])) { 
            token_array[tc_ptr++] = token;
            token.clear();

        }
        else {
            token.push_back(line[i]);
        }
        i++;
    }
    token_array[tc_ptr++] = token; // необходимо для строки, незаконченной пробелом
    token.clear();
    return token_array;
}

void output_tokens(string* token_array, size_t& tc_ptr) {
    cout << tc_ptr << endl;
    cout << "<";
    for (size_t i = 0; i < tc_ptr; ++i) {
        cout << "> " << token_array[i] << " <";
    }
    cout << ">";
    cout << endl;
}