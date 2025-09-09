#include <iostream>
#include "tokenizator.h"
#include "token_converter.h"

using namespace std;
int main()
{
	string line = input();
	size_t token_count;
	string* token_array= tokenize(line, token_count);
	

	//output_tokens(token_array, tc_ptr);

	size_t max_instr = 10;
	size_t max_tacts = 20;
	string** grid = array2d_init(max_instr);
	tokens_to_grid(token_array, grid, token_count, max_instr);
	//size_t after_burn_instr = count_instr(token_array, token_count);
	cout << endl << "output: " << endl << endl;
	output_grid(grid, max_instr, max_tacts);
}
