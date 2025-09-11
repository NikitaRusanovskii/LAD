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
	//������ ���� ��� �������
	string** grid;
	vector<double> memory;
	//Ram
	// 
	//ca� ������ 
	Remote* remote;

	Command* com = nullptr; // ���� �� ��������� ����������� ���������


	map<string, Command*> instructions;


	//����� ���� ������� ������

public:


	Interpretator(string** _grid, vector<double> _memory);
	~Interpretator()
	{
		//
	}

	void executeCommand();

	void setCommand(Command* _com);


	void Interpretate();

};