#pragma once
#include <iostream>
#include <string>
#include "tokenizator.h"


const size_t max_tacts = 20;

const string empty_cell = " .";

const unordered_set<string> arithmetical_coms = { "add", "sub", "mul", "div", "inc" }; // 3 arg
const unordered_set<string> jump_coms = { "jmp", "je", "jne", "jg", "jge", "jl", "jle"}; // 1 arg
const unordered_set<string> memory_coms = { "ld", "st", "mv"}; // 2 arg
const unordered_set<string> all_coms = { "add", "sub", "mul", "div", "inc",
"jmp", "je", "jne", "jg", "jge", "jl", "jle",  "ld", "st", "mv", "cmp"};

string** array2d_init(size_t instr);
bool is_instruction(string token, const unordered_set<string> type_coms);
string delete_first_char(const string token);
string delete_last_char(string token);
bool is_register(string token);
bool is_address(string token);
int count_instr(string* tokens, size_t& token_count);
void tokens_to_grid(string* tokens, string** &grid, size_t& token_count);
bool is_valid_jmpcmd(string** grid, size_t iptr);
bool is_valid_memcmd(string** grid, size_t iptr);
bool is_valid_arithmcmd(string** grid, size_t iptr);
int is_valid_grid(string** grid, size_t instr_amount);
void refresh_grid(string**& grid, size_t instr);
void output_grid(string** grid, size_t instr, size_t tacts);

bool is_instruction(string token, const unordered_set<string> type_coms) {
    to_lower_letter(token);
    return type_coms.find(token) != type_coms.end();
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

bool is_address(string token) {
    return token[0] == '[' && is_number(delete_last_char(delete_first_char(token))) &&
        token[token.size()-1] == ']';
}

string** array2d_init(size_t instr) {
  string** grid = new string*[instr];
  for (size_t i = 0; i < instr; ++i) {
    grid[i] = new string[max_tacts];
    for (size_t t = 0; t < max_tacts; t++) {
        grid[i][t] = empty_cell;
    }
  }
  return grid;
}

string delete_first_char(const string token) {
    return token.size() > 1 ? token.substr(1) : "";
}

string delete_last_char(string token) {
    token.pop_back();
    return token.size() > 1 ? token : "";
}

int count_instr(string* tokens, size_t& token_count) {
    int res=0;
    for (size_t i = 0; i < token_count; i++) {
        if (is_instruction(tokens[i], all_coms)) res++;
    }
    return res;
}

void tokens_to_grid(string* tokens, string** &grid, size_t& token_count) {
    size_t j = 0, i=0;
    size_t instr_amount = count_instr(tokens, token_count);
    while(j<token_count && i < instr_amount) {
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
    refresh_grid(grid, instr_amount);
}

bool is_valid_jmpcmd(string** grid, size_t iptr) {
    bool res = true;
    if (!is_address(grid[iptr][2]) || grid[iptr][3]!=empty_cell || 
        grid[iptr][4] != empty_cell) {
        res = false;
    }
    return res;
}

bool is_valid_memcmd(string** grid, size_t iptr) {
    bool res = true;
    if (grid[iptr][1] == "ld") {
        if (!is_address(grid[iptr][2]) || !is_register(grid[iptr][3]) ||
            grid[iptr][4] != empty_cell) {
            res = false;
        }
    }
    else if (grid[iptr][1] == "st") {
        if (!is_register(grid[iptr][2]) || !is_address(grid[iptr][3]) ||
            grid[iptr][4] != empty_cell) {
            res = false;
        }
    }
    return res;
}

bool is_valid_arithmcmd(string** grid, size_t iptr) {
    bool res = true;
    for (int i = 2; i < 5; i++) {
        if (!is_register(grid[iptr][i])) res = false;
    }
    return res;
}

int is_valid_grid(string** grid, size_t instr_amount) {
   int res = 0;
    for (size_t i = 0; i < instr_amount; i++) {
        string curcmd = grid[i][1];
        if (!is_number(grid[i][0])) {
            res = 1; cout << endl <<  " >> " << grid[i][0] << " << " << endl;
        }
        else if (!is_instruction(curcmd, all_coms)) {
            res = 2;
        }
        else if (is_instruction(curcmd, memory_coms) && !is_valid_memcmd(grid, i)) {
            res = 21;
        }
        else if (is_instruction(curcmd, arithmetical_coms) && !is_valid_arithmcmd(grid, i)) {
            res = 22;
        }
        else if (is_instruction(curcmd, jump_coms) && !is_valid_jmpcmd(grid, i)) {
            res = 23;
        }
    }
    return res;
}

void refresh_grid(string** &grid, size_t instr) {
    string** tmp_grid = array2d_init(instr);
    for (int i = 0; i < instr; i++) {
        for (int j = 0; j < max_tacts; j++) {
            tmp_grid[i][j] = grid[i][j];
        }
    }
    free(grid);
    grid = array2d_init(instr);
    for (int i = 0; i < instr; i++) {
        for (int j = 0; j < max_tacts; j++) {
            grid[i][j] = tmp_grid[i][j];
        }
    }
    free(tmp_grid);
}

void output_grid(string** grid, size_t instr, size_t tacts) {
  for (size_t i = 0; i < instr; ++i) {
    for (size_t t = 0; t < tacts; ++t) {
      cout << " " << grid[i][t] << " ";
    }
    cout << endl;
  }
  string ans = "valid";
  if (is_valid_grid(grid, instr) == 1) {
      ans = "invalid. Error 1";
  }
  else if (is_valid_grid(grid, instr) == 2) {
      ans = "invalid. Error 2";
  }
  else if (is_valid_grid(grid, instr) == 21) {
      ans = "invalid. Error 21";
  }
  else if (is_valid_grid(grid, instr) == 22) {
      ans = "invalid. Error 22";
  }
  else if (is_valid_grid(grid, instr) == 23) {
      ans = "invalid. Error 23";
  }
  cout << "grid is " << ans << endl;
}