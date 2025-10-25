#include <iostream>
#include "Interpretator.h"
#include "Helpers.h"
#include"Memory.h"
#include"Grid.h"

using namespace std;

int main()
{



	//string** mem = new string * [3];
	//for (int i = 0; i < 3; i++)
	//{
	//	mem[i] = new string[2];
	//}
	//mem[0][0] = "[1000]";
	//mem[0][1] = "12";
	//mem[1][0] = "[1004]";
	//mem[1][1] = "3";
	//mem[2][0] = "[1008]";
	//mem[2][1] = "4";
	//vector<double> memory = memory_hash(mem, 3);
	//cout << memory[(1000 - 1000) / 4] << endl;
	//cout << memory[(1004 - 1000) / 4] << endl;
	//cout << endl;
	//cout << endl;

	Memory m = Memory();
	m.add(1000, 12);
	m.add(1004, 3);
	m.add(1008, 4);
	cout << m<<endl;
	
	string s = "ld   [1008], r1          ld [1000] r2 sub r1 r2 r3 st r3 [1008]";
	Grid grid(s);




	// список инструкций и их реалезация находится в Remote
	// Потомки Command  - классы, объекты которых исполняют соответствующую инструкцию
	// Interpretator - клиент, хранящий варианты команд как объекты, ставящий их взависимости от условия и исполняющий их
	//все они очень слабо зависят друг от друга и очень легко заменяемы, также крайне удобно дебажить


	Interpretator* inter = new Interpretator(grid.getSize(), &grid, &m);
	inter->Interpretate();
	cout << m << endl;
}
