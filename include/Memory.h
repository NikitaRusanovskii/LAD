#pragma once


#include <map>
#include <vector>
#include <iostream>
using namespace std;




class Memory
{
	vector<pair<int, double>> memory;
	vector<bool> type_indicators; //true == double false == int

public:
	Memory();
	Memory(const Memory& mem);
	vector<bool> getTypes();

	//добавление
	void add(const int address, const double value);
	void add(const int address, const int value);

	//сохранение
	void store(const int address, const double value);
	void store(const int address, const int value);

	//чтение
	const double& operator[](const int address) const;
	bool contains(const int& address) const;



	friend ostream& operator<<(ostream& ostr, const Memory& mem);
};

