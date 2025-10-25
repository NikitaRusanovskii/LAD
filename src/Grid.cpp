#include <iostream>


#include "RegularStorage.h"
#include"Grid.h"

Grid::Grid(string _s) : s(_s)
{
    keywords = {
        "ld", "st", "mov",
        "add", "sub", "mul", "div",
        "fadd", "fsub", "fmul", "fdiv",
        "and", "or", "xor", "not",
        "shl", "shr", "inc", "dec",
        "cmp", "jmp", "je", "jne" "jl", "jle", "jg", "jge"
    };
    to_lower_letter(s);
    gridCreator(splitByInstructionsNames(s));
    size = grid.size();
}

void Grid::to_lower_letter(string& token) {
    for (char& c : token) {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));//faster and safer than transfoem()
    }
}

int Grid::getSize()
{
    return size;
}


vector<string> Grid::splitByInstructionsNames(string input) {

    vector<string> result;

    size_t start = 0;
    size_t pos = 0;
    bool potential_match = false;
    const size_t len = input.length();

    while (pos < len) {
        // Быстрая проверка первого символа - большинство ключевых слов начинаются с разных букв
        const char current_char = input[pos];
        //bool potential_match = false;

        // Предварительная фильтрация по первому символу
        switch (current_char) {
        case 'l': case 'a': case 's': case 'm': case 'd':case 'f':
        case 'o': case 'x': case 'n': case 'i': case 'c':case 'j':
            potential_match = true;
            break;
        default:
            bool potential_match = false;
        }

        if (potential_match) {
            bool keyword_found = false;

            // Проверяем только релевантные ключевые слова
            for (const auto& keyword : keywords) {
                if (keyword[0] == current_char &&
                    pos + keyword.length() <= len &&
                    input.compare(pos, keyword.length(), keyword) == 0) {

                    // Проверяем, что это отдельное слово (не часть другого слова)
                    if (input[pos + keyword.length()] != ' ') {
                        break;
                    }


                    if (pos > start) {
                        result.emplace_back(input.substr(start, pos - start));
                    }
                    start = pos;
                    keyword_found = true;
                    break;
                }
            }

            if (keyword_found) {

                pos++;// Перескакиваем на следующий символ
                continue;  // Пропускаем pos++ в конце цикла
            }
        }

        pos++;
    }

    // Добавляем остаток
    if (start < len) {
        result.emplace_back(input.substr(start));
    }

    return result;
}
/*
1.pos = 0: Видим 'l' → potential_match = true

    Проверяем keywords : "ld"[0] == 'l' → да!

    Проверяем границы : pos = 0 → это начало строки

    Добавляем : (пока ничего)

    start = 0, pos = 1, continue

2. pos = 1 : Обычный символ 'd' → potential_match = false → pos++

3. pos = 2 - 11 : Обычные символы[1008] r1 → pos++

4. pos = 12 : Видим 'a' → potential_match = true

    Проверяем keywords : "add"[0] == 'a' → да!

    Проверяем полное совпадение : "add" == "add" → да!

    Проверяем границы : перед 'a' пробел → отдельное слово

    Добавляем : "ld [1008] r1 "

    start = 12, pos = 13, continue

5. pos = 13 - 20 : Обычные символы → pos++

6. Конец : Добавляем "add r1 r2"
    и так по кругу
7. в итоге получаем вектор из инструкций, который проверяем с помощью RegexStorage
*/


void Grid::gridCreator(vector<string> instructions)
{
    grid.reserve(instructions.size());
    for (size_t i = 0; i < instructions.size(); i++)
    {
        bool found = false;
        for (regex r : RegularStorage::Instance()->getInstructionsStorage())
        {
            smatch matches;
            if (regex_match(instructions[i], matches, r))
            {
                found = true;

                vector<string> uresult;
                for (size_t j = 1; j < matches.size(); j++)
                {
                    uresult.push_back(matches[j].str());
                }
                grid.push_back(uresult);
                break;
            }
        }
        if (!found)
        {
            throw runtime_error("Instruction in line: " + to_string(i * 4) + " is invalid");
        }
    }
};


const vector<string>& Grid::operator[](int ind) const
{
    return grid[ind];
}

const vector<string>& Grid::at(int ind) const
{
    if (ind > size)
        throw out_of_range("Нет инструкции с таким номером");
    if (ind < 0)
        throw out_of_range("Нет инструкции с отрицательным номером");
    return grid[ind];
}

bool Grid::contains(const int& ind) const
{
    if (ind < grid.size())
        return true;
    return false;
}

ostream& operator<<(ostream& ostr, const vector<string> v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        ostr << v[i] << " ";
    }
    cout << endl;
    return ostr;
}

ostream& operator<<(ostream& ostr, const Grid& grid)
{
    for (int i = 0; i < grid.size; i++) {
        ostr << (i * 4 > 10 ? to_string(i * 4) : ("0" + to_string(i * 4))) << " " << grid[i];
    }
    return ostr;
}

