#pragma once
#include <iostream>
#include <string>
#include "tokenizator.h"

unordered_set<string> arithmetical_coms = { "add", "sub", "mul", "div", "inc" }; // 3 arg
unordered_set<string> jump_coms = { "jmp", "je", "jne", "jg", "jge", "jl", "jle"}; // 1 arg
unordered_set<string> memory_coms = { "ld", "st", "mv"}; // 2 arg
unordered_set<string> all_coms = { "add", "sub", "mul", "div", "inc",
"jmp", "je", "jne", "jg", "jge", "jl", "jle",  "ld", "st", "mv", "cmp"};

string** array2d_init(size_t max_instr, size_t max_tacts) {
  string** grid = new string* [max_instr];
  for (size_t i = 0; i < max_instr; ++i) {
    grid[i] = new string[max_tacts];
    for (size_t t = 0; t < max_tacts; t++) {
        grid[i][t] = ". ";
    }
  }
  return grid;
}




void to_lower_letter(string& token) {
    transform(token.begin(), token.end(), token.begin(), ::tolower);
}

bool is_instruction(string token, unordered_set<string> type_coms) {
    to_lower_letter(token);
    return type_coms.find(token) != type_coms.end();
}

string delete_first_char(const string token) {
    return token.size() > 1 ? token.substr(1) : "";
}

bool is_number(string token) {
    bool flag = 1;
    if (token.empty()) flag = 0;
    for (char s : token) {
        if (!isdigit(s)) flag = 0;
    }
    return flag;
}

bool is_register(string token) {
    to_lower_letter(token);
    return token[0] == 'r' && is_number(delete_first_char(token));
}
int count_instr(string* tokens, size_t& tc_ptr) {
    int res=0;
    for (size_t i = 0; i < tc_ptr; i++) {
        if (is_instruction(tokens[i], all_coms)) res++;
    }
    return res;
}
void tokens_to_grid(string* tokens, string** grid, size_t& tc_ptr) {
    size_t j = 0, i=0;
    size_t instr_amount = count_instr(tokens, tc_ptr);
    while(j<tc_ptr && i < instr_amount) {
        grid[i][0] = to_string(i * 4);
        string current_com = tokens[j];
        grid[i][1] = tokens[j++];
        grid[i][2] = tokens[j++];
        if (is_instruction(current_com, memory_coms) || tokens[j] == "cmp") {
            grid[i][3] = tokens[j++];
        }
        else if (is_instruction(current_com, arithmetical_coms)) {
            grid[i][3] = tokens[j++];
            grid[i][4] = tokens[j++];
        }
        i++;
    }
}
bool is_valid_memcmd(string** grid, size_t iptr) {
    bool res = true;
    return res;
}

bool is_valid_arithmcmd(string** grid, size_t iptr) {
    bool res = true;
    for (int i = 2; i < 5; i++) {
        if (!is_register(grid[iptr][i])) res = false;
    }
    return res;
}


bool is_valid_grid(string** grid, size_t instr_amount) {
    bool res = true;
    for (size_t i = 0; i < instr_amount; i++) {
        if (!is_number(grid[i][0])) res = false;
        else if (!is_instruction(grid[i][1], all_coms)) res = false;
        else if (is_instruction(grid[i][1], memory_coms)) {

        }
        else if (is_instruction(grid[i][1], arithmetical_coms)) {

        }
    }
    return res;
}

void output_grid(string** grid, size_t instr, size_t tacts) {
  cout << "tacts: " << tacts << "  2d array: " << endl;
  for (size_t i = 0; i < instr; ++i) {
    for (size_t t = 0; t < tacts; ++t) {
      cout << " " << grid[i][t] << " ";
    }
    cout << endl;
  }
}