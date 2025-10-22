#include "Memory.h"
#include<iostream>


Memory::Memory()
{

}

Memory::Memory(const Memory& mem) : memory(mem.memory)
{
}

vector<bool> Memory::getTypes()//следует позже сунуть в protected или вообще убрать
{
	return type_indicators;
}


void Memory::add(const int address, const double value)
{
	memory.emplace_back(address, value);//добавляем pair<address, value>
	type_indicators.push_back(true);//записываем, то что это double
}

void Memory::add(const int address, const int value)
{
	memory.emplace_back(address, value);//добавляем pair<address, value>
	type_indicators.push_back(false);//записываем, то что это int
}

void Memory::store(const int address, const double value)//версия для double
{
	for (size_t i = 0; i < memory.size(); i++)
	{
		if (memory[i].first == address)//ищем пару в которой ключ == address
		{
			if (!type_indicators[i])
				throw - 4;//wrong address
			memory[i].second = value;//переписываем
			return;//ливаем
		}
	}
	throw "address doesnot exists";
}

void Memory::store(const int address, const int value)//версия для int
{	
	for (size_t i = 0; i < memory.size(); i++)
	{
		if (memory[i].first == address)
		{
			if (type_indicators[i])
				throw - 4; //wrong address
			memory[i].second = value;
			return;//ливаем
		}
	}
	throw "address doesnot exists";
}

const double& Memory::operator[](const int address) const //только чтение
{
	for (const auto& pair : memory)
		if (pair.first == address)
			return pair.second;
}

bool Memory::contains(const int& address) const
{
	for (const auto& pair : memory)
		if (pair.first == address)
			return true;
	return false;
}


ostream& operator<<(ostream& ostr, const Memory& mem)
{
	for (auto& pair : mem.memory)
	{
		ostr << pair.first << " " << pair.second << endl;
	}
	return ostr;
}