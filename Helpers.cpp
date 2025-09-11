#include"Helpers.h"

double digit_getter_f(string s)
{
	string res = "";
	for (char o : s)
		if (isdigit(o) || o == '.')
			res += o;
	return stod(res);
}

vector<double> memory_hash(string** grid, int n)
{
	vector<double> memory;
	for (int i = 0; i < n; i++)
	{
		int number = (digit_getter_f(grid[i][0]) - 1000) / 4;
		if (number > memory.size())
		{
			memory.push_back(0);
			memory.push_back(digit_getter_f(grid[i][1]));
		}
		else
		{
			memory.push_back(digit_getter_f(grid[i][1]));
		}
	}
	return memory;
}