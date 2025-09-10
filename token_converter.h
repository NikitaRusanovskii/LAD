#pragma once
#include <iostream>
#include <string>
#include <array>
#include "tokenizator.h"
//#include "instruction.h"

const size_t max_tacts = 20;
int error = 0;
const string empty_cell = " .";


struct cmd {
    const string name;
    const char arg1; // 0 == there should be no argument. 1 == there should be int register. 
    const char arg2;  // 2 == there should be float register. 3 == there should be address.
    const char arg3;
    const int arg_amount;

    cmd(string name, char arg1, char arg2, char arg3, int arg_am)
        : name(move(name)), arg1(arg1), arg2(arg2), arg3(arg3), arg_amount(arg_am) {
    }
};

string** array2d_init(size_t instr);
bool is_instruction(string token);
string delete_first_char(const string token);
string delete_last_char(string token);
bool is_register(string token);
bool is_address(string token);
//int count_instr(string* tokens, size_t& token_count);
void tokens_to_grid(string* tokens, string** &grid, size_t& token_count, size_t& ic);
int is_valid_grid(string** grid, size_t instr_amount);
void refresh_grid(string**& grid, size_t instr);
void output_grid(string** grid, size_t instr, size_t tacts);

array<cmd, 20> cmd_array = { {
    {"add", 'r', 'r', 'r', 3}, {"fadd", 'f', 'f', 'f', 3},  // arithmetic
    {"sub", 'r', 'r', 'r', 3}, {"fsub", 'f', 'f', 'f', 3},
    {"mul", 'r', 'r', 'r', 3}, {"fmul", 'f', 'f', 'f', 3},
    {"div", 'r', 'r', 'r', 3}, {"fdiv", 'f', 'f', 'f', 3},
    {"inc", 'r', ' ', ' ', 1},

    {"cmp", 'r', 'r', ' ', 2},  // jmps
    {"jmp", 'a', ' ', ' ', 1},
    {"je",  'a', ' ', ' ', 1},
    {"jne", 'a', ' ', ' ', 1},
    {"jl",  'a', ' ', ' ', 1},
    {"jle", 'a', ' ', ' ', 1},
    {"jg",  'a', ' ', ' ', 1},
    {"jge", 'a', ' ', ' ', 1},


    {"mv", 'r', 'r', ' ', 2}, // memory
    {"ld", 'a', 'r', ' ', 2},
    {"st", 'r', 'a', ' ', 2}
} };

bool is_instruction(string token) {
    to_lower_letter(token);
    bool res = false;
    for (size_t i = 0; i < cmd_array.size(); i++) {
        if (token == cmd_array[i].name) { 
            res = true;
            break;
        }
    }
    return res;
}

size_t cmd_pos(string cmd) {
    to_lower_letter(cmd);
    size_t res = -1;
    for (size_t i = 0; i < cmd_array.size(); i++) {
        if (cmd == cmd_array[i].name) { 
            res = i;
            break;
        }
    }
    return res; // if no cmd in array returns -1
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
    return (token[0] == 'r' || token[0] == 'f') && is_number(delete_first_char(token));
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


void tokens_to_grid(string* tokens, string** &grid, size_t& token_count, size_t& ic) {
    size_t j = 0;
    ic = 0;
    //size_t instr_amount = count_instr(tokens, token_count);
    //if (instr_amount == 0) { error = -120; } // no instructions error or wrong instruction
    while(j<token_count) {
        grid[ic][0] = to_string(ic * 4); // instruction number * 4
        string current_com = tokens[j++];
        size_t aptr = cmd_pos(current_com);
        if (aptr == -1) { error = -130; break; } // wrong instruction error
        grid[ic][1] = current_com;
        if (cmd_array[aptr].arg_amount == 1) { // cmd has 1 arg
            grid[ic][2] = tokens[j++];
        }
        else if (cmd_array[aptr].arg_amount == 2) { // cmd has 2 args
            grid[ic][2] = tokens[j++];
            grid[ic][3] = tokens[j++];
        }
        else if(cmd_array[aptr].arg_amount == 3){ // cmd has 3 args
            grid[ic][2] = tokens[j++];
            grid[ic][3] = tokens[j++];
            grid[ic][4] = tokens[j++];
        }
        ic++;
    }
    refresh_grid(grid, ic);
}
int is_valid_line(string** grid, size_t iptr) {
    int res = 0;
    if (!is_number(grid[iptr][0])) {
            res = -104; // instruction number isnt correct error
    }
    size_t cmd_type = cmd_pos(grid[iptr][1]);
    if (cmd_type == -1) { res = -100; } // there s no such cmd error
    else {
        char cmd_arg1 = grid[iptr][2][0];
        char cmd_arg2 = grid[iptr][3][0];
        char cmd_arg3 = grid[iptr][4][0];

        if (cmd_arg1 == '[') cmd_arg1 = 'a';
        if (cmd_arg2 == '[') cmd_arg2 = 'a';
        if (cmd_arg3 == '[') cmd_arg3 = 'a';

        if (!is_address(grid[iptr][2]) && !is_register(grid[iptr][2])
            && cmd_array[cmd_type].arg_amount >= 1) { res = -101; } // 1st arg error

        if (!is_address(grid[iptr][3]) && !is_register(grid[iptr][3])
            && cmd_array[cmd_type].arg_amount >= 2) { res = -102; } // 2nd arg error

        if (!is_address(grid[iptr][4]) && !is_register(grid[iptr][4])
            && cmd_array[cmd_type].arg_amount == 3) { res = -103; } // 3rd arg error

        if(cmd_array[cmd_type].arg1!=cmd_arg1 || cmd_array[cmd_type].arg2 != cmd_arg2 ||
            cmd_array[cmd_type].arg3 != cmd_arg3) {
            res = -110; // doesnt match arg types error
        }
    }
    
    return res;
}
int is_valid_grid(string** grid, size_t instr_amount) {
   int res = 0;
    for (size_t i = 0; i < instr_amount; i++) {
        res = is_valid_line(grid, i);
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
  if (error == 0) {
      error = is_valid_grid(grid, instr);
  }
  
  if (error != 0) {
      ans = "invalid. Error " + to_string(error) + ".";
  }

  cout << "grid is " << ans << endl;
}