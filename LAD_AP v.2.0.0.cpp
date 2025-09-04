#include <iostream>
#include "tokenizator.h"
#include "token_converter.h"

using namespace std;
int main()
{
	string line = input();

	string* token_array;
	size_t tc_ptr;
	token_array = tokenize(line, tc_ptr);
	output_tokens(token_array, tc_ptr);

	size_t max_instr = 10;
	size_t max_tacts = 20;
	string** grid = array2d_init(max_instr, max_tacts);
	tokens_to_grid(token_array, grid, tc_ptr);
	output_grid(grid, max_instr, max_tacts);
}
