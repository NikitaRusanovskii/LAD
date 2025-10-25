#pragma once
#include <vector>
#include <string>
#include <array>

using namespace std;

class Grid
{
    string s;
    int size;
    vector<vector<string>>grid;
    array<string, 28> keywords;
public:
    Grid(string _s);


    vector<string> splitByInstructionsNames(string input);
    void gridCreator(vector<string> instructions);
    void to_lower_letter(string& token);
    int getSize();

    const vector<string>& operator[](int address) const;
    const vector<string>& at(int ind) const;


    bool contains(const int& address) const;



    friend ostream& operator<<(ostream& ostr, const Grid& grid);
};

ostream& operator<<(ostream& ostr, const vector<string> v);