#pragma once

#include <vector>
#include <regex>

using namespace std;



class RegularStorage
{
private:
	static RegularStorage* _instance;
	static vector<regex> instructions_storage;
	static vector<regex> memory_storage;
protected:
	RegularStorage();
public:
	static RegularStorage* Instance();
	const vector<regex>& getInstructionsStorage();//safe and without copy because of static and const
	const vector<regex>& getMemoryStorage();//safe and without copy because of static and const
};