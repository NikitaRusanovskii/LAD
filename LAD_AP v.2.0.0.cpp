#include <iostream>
#include "tokenizator.h"
#include "token_converter.h"
#include "Interpretator.h"
#include "Helpers.h"

using namespace std;

int main()
{
	string line = input();
	size_t token_count;
	string* token_array= tokenize(line, token_count);
	size_t max_instr = 10;
	size_t max_tacts = 20;
	string** grid = array2d_init(max_instr);
	tokens_to_grid(token_array, grid, token_count, max_instr);

	cout << endl << "output: " << endl << endl;
	output_grid(grid, max_instr, max_tacts);



	string** mem = new string * [3];
	for (int i = 0; i < 3; i++)
	{
		mem[i] = new string[2];
	}
	mem[0][0] = "[1000]";
	mem[0][1] = "12";
	mem[1][0] = "[1004]";
	mem[1][1] = "3";
	mem[2][0] = "[1008]";
	mem[2][1] = "4";
	vector<double> memory = memory_hash(mem, 3);
	cout << memory[(1000 - 1000) / 4] << endl;
	cout << memory[(1004 - 1000) / 4] << endl;
	cout << endl;
	cout << endl;

	//string** grid = new string * [4];
	//for (int i = 0; i < 4; i++)
	//{
	//	grid[i] = new string[4];
	//}

	//grid[0][0] = "ld";
	//grid[0][1] = "[1000]";
	//grid[0][2] = "r1";
	//grid[1][0] = "ld";
	//grid[1][1] = "[1004]";
	//grid[1][2] = "r2";
	//grid[2][0] = "add";
	//grid[2][1] = "r1";
	//grid[2][2] = "r2";
	//grid[2][3] = "r3";
	//grid[3][0] = "nop";


	// список инструкций и их реалезация находится в Remote
	// Потомки Command  - классы, объекты которых исполняют соответствующую инструкцию
	// Interpretator - клиент, хранящий варианты команд как объекты, ставящий их взависимости от условия и исполняющий их
	//все они очень слабо зависят друг от друга и очень легко заменяемы, также крайне удобно дебажить


	Interpretator* inter = new Interpretator(grid, memory);
	inter->Interpretate();
}
