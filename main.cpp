#include "Interpretator.h"

#include "Helpers.h"



int main()
{
	string** mem = new string*[3];
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



	int ammount = 4;
	string** grid = new string*[4];
	for (int i = 0; i < ammount; i++)
	{
		grid[i] = new string[4];
	}

	grid[0][0] = "jge";
	grid[0][1] = "[+8]";
	grid[0][2] = "r1";
	grid[1][0] = "ld";
	grid[1][1] = "[1004]";
	grid[1][2] = "r2";
	grid[2][0] = "add";
	grid[2][1] = "r1";
	grid[2][2] = "r2";
	grid[2][3] = "r3";
	grid[3][0] = "nop";
	

	// список инструкций и их реалезаци€ находитс€ в Remote
	// ѕотомки Command  - классы, объекты которых исполн€ют соответствующую инструкцию
	// Interpretator - клиент, хран€щий варианты команд как объекты, став€щий их взависимости от услови€ и исполн€ющий их
	//все они очень слабо завис€т друг от друга и очень легко замен€емы, также крайне удобно дебажить
	

	Interpretator* inter = new Interpretator(ammount ,grid, memory);
	inter->Interpretate();
	
	return 0;

}