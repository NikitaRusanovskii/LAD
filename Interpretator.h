#pragma once
#include<map>
#include<string>
#include<vector>
#include <iostream>

using namespace std;



class Remote;
class Command;
class Interpretator
{
	int n;
	int iter;
	//нужные поля для ремоута
	string** grid;
	vector<double> memory;

	//Ram
	// 
	//caм ремоут 
	Remote* remote;

	Command* com = nullptr; // сюда мы загружаем исполняемую программу


	
	
	map<string, Command*> instructions;

	//набор всех классов команд

public:


	Interpretator(int _n, string** _grid, vector<double> _memory);
	~Interpretator();

	void executeCommand();

	void setCommand(Command* _com);


	void Interpretate();

};