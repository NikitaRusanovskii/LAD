#pragma once
#include<map>
#include<string>
#include<vector>
#include <iostream>

using namespace std;



class Remote;
class Command;
class Memory;
class Grid;
class Interpretator
{
	int n;
	int iter;
	//нужные поля для ремоута
	Grid* grid;
	Memory* memory;

	//Ram
	// 
	//caм ремоут 
	Remote* remote;

	Command* com = nullptr; // сюда мы загружаем исполняемую программу


	
	
	map<string, Command*> instructions;

	//набор всех классов команд

public:


	Interpretator(int _n, Grid* _grid, Memory* _memory);
	~Interpretator();

	void executeCommand();

	void setCommand(Command* _com);


	void Interpretate();

};