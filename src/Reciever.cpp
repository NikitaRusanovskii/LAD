#include "Reciever.h"
#include "Helpers.h"
#include "Memory.h"




regex pattern_reg_reg("\\[\\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\\s*(\\+|\\-)\\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\\s*\\]");
regex pattern_const_reg("\\[\\s*(\\d+)\\s*(\\+|\\-)\\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\\s*\\]");
regex pattern_reg_const("\\[\\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\\s*(\\+|\\-)\\s*(\\d+)\\s*\\]");
regex pattern_const("\\[\\s*(\\d+)\\s*\\]");
regex pattern_reg("\\[\\s*[Rr](0|[1-9]|[1-2][0-9]|3[0-2])\\s*\\]");
smatch matches;


#define REG(x) registers[digit_getter(grid[current_instruction][x])]
#define REGF(x) registers_f[digit_getter(grid[current_instruction][x])]
#define MEM(x) memory[(ld_st_address_converter(grid[current_instruction][x])-1000)/4]
#define MEMR(x) (*memory)[ld_st_address_converter(grid[current_instruction][x])]
#define MEMW(x, v) (*memory).store(ld_st_address_converter(grid[current_instruction][x]), v)




Remote::Remote(string** _grid, Memory* _memory)
{
	registers = new int[32];
	registers_f = new double[64];

	current_instruction = 0;

	grid = _grid;
	memory = _memory;
}
int Remote::digit_getter(string s)
{
	string res = "";
	for (char o : s)
		if (isdigit(o))
			res += o;
	return stoi(res);
}

int Remote::jmp_address_detection(string token)
{
	int res;
	switch (token[1])
	{
	case '+':
		res = 1;
		break;
	case '-':
		res =  -1;
		break;
	default:
		res = 0;
		break;
	}
	return res;
}

int Remote::ld_st_address_converter(string s)
{
	int res;
	int i = 0;
	if (regex_search(s, matches, pattern_reg_reg))
	{
		i = matches[2] == '+' ? 1 : -1;
		res = registers[stoi(matches[1].str())] + i*registers[stoi(matches[3].str())];
	}
	else if (regex_search(s, matches, pattern_const_reg))
	{
		i = matches[2] == '+' ? 1 : -1;
		res = stoi(matches[1].str()) + i*registers[stoi(matches[3].str())];
	}
	else if (regex_search(s, matches, pattern_reg_const))
	{
		i = matches[2] == '+' ? 1 : -1;
		res = registers[stoi(matches[1].str())] + i*stoi(matches[3].str());
	}
	else if (regex_search(s, matches, pattern_const))
	{
		res = stoi(matches[1].str());
	}
	else if (regex_search(s, matches, pattern_reg))
	{
		res = registers[stoi(matches[1].str())];
	}
	else
	{
		throw - 1;
	}
	address_checker(res);
	return res;
}

int* Remote::getRegisters()
{
	return registers;
}

int& Remote::getCurrInst()
{
	return current_instruction;
}

void Remote::ADD()
{
	REG(3) = REG(1) + REG(2);
}

void Remote::FADD()
{
	REGF(3) = REGF(1) + REGF(2);//f3
}

void Remote::SUB()
{
	REG(3) = REG(1) - REG(2);
}

void Remote::FSUB()
{
	REGF(3) = REGF(1) - REGF(2);
}

void Remote::MUL()
{
	REG(3) = REG(1) * REG(2);
}

void Remote::FMUL()
{
	REGF(3) = REGF(1) * REGF(2);
}

void Remote::DIV()
{
	int r1 = REG(1);
	int r2 = REG(2);
	if (r2 == 0) return; // ��� ������ �� ���������
	REG(3) = REG(1) / REG(2);
	REG(4) = REG(1) % REG(2);
}

void Remote::FDIV()
{
	if (REGF(2) == 0) return; // ��� ������ �� ���������
	REGF(3) = REGF(1) / REGF(2);
}

void Remote::AND()
{
	REG(3) = REG(1) & REG(2);
}

void Remote::OR()
{
	REG(3) = REG(1) | REG(2);
}

void Remote::NOT()
{
	REG(2) = ~REG(1);
}

void Remote::XOR()
{
	REG(3) = REG(1) ^ REG(2);
}


void Remote::SHR()
{
	if ((REG(2) >= (sizeof(int) * 8)) || (REG(2) < 0)) return;
	REG(3) = (int)REG(1) >> (int)REG(2);
}

void Remote::SHL()
{
	// ��������� ������ ������. �������� R1 �� R2, ���������� � R3
	// ��������� if ��� ������ �� UBR
	if ((REG(2) >= (sizeof(int) * 8)) || (REG(2) < 0)) return;
	REG(3) = REG(1) << REG(2);

}

void Remote::CMP()
{
	if (REG(1) == REG(2)) {
		this->flag = 0;
	}
	else if (REG(1) <= REG(2)) { // ������� � ����� ������� � ���� flag �������� ����� ��� JNE
		this->flag = -2;
	}
	else if (REG(1) < REG(2)) {
		this->flag = -1;
	}
	else if (REG(1) >= REG(2)) {
		this->flag = 2;
	}
	else if (REG(1) > REG(2)) {
		this->flag = 1;
	}
}

void Remote::INC()
{
	REG(1)++;
}

void Remote::DEC()
{
	REG(1)--;
}

void Remote::JMP() {
	// ��������� ������� �����������, �� ������� ���������� �������� ��������� �� ����������
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) != 0) return;
	int addr = digit_getter(p);
	this->current_instruction = (addr / 4 - 1);//?? почему -1?
}

void Remote::JE() {
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) == 0) return;
	if (this->flag != 0) return;
	int addr = digit_getter(p) * jmp_address_detection(p);
	this->current_instruction = (this->current_instruction + (addr / 4));
}

void Remote::JNE() {
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) == 0) return;
	if (this->flag == 0) return; // ����� ������ ��� ���� ���� jne ��� ������ �����
	int addr = digit_getter(p) * jmp_address_detection(p);
	this->current_instruction = (this->current_instruction + (addr / 4));
}

void Remote::JL() {
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) == 0) return;
	if (this->flag != -1) return;
	int addr = digit_getter(p) * jmp_address_detection(p);
	this->current_instruction = (this->current_instruction + (addr / 4));
}

void Remote::JLE() {
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) == 0) return;
	if (this->flag != -2) return;
	int addr = digit_getter(p) * jmp_address_detection(p);
	this->current_instruction = (this->current_instruction + (addr / 4));
}

void Remote::JG() {
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) == 0) return;
	if (this->flag != 1) return;
	int addr = digit_getter(p) * jmp_address_detection(p);
	this->current_instruction = (this->current_instruction + (addr / 4));
}

void Remote::JGE() {
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) == 0) return;
	if (this->flag != 2) return;
	int addr = digit_getter(p) * jmp_address_detection(p);
	this->current_instruction = (this->current_instruction + (addr / 4));
}

void Remote::LD()
{
	// ��������� ������ ����� ��������
	if (grid[current_instruction][2][0] == 'r')
	{
		int f = 2;
		
		REG(2) = MEMR(1);
	}
	else
	{
		REGF(2) = MEMR(1);
	}
}

void Remote::ST()
{
	if (grid[current_instruction][1][0] == 'r')
	{
		try
		{
			MEMW(2, REG(1));
		}
		catch (int)
		{
			cout << "Нельзя записывать int на место double";
		}
	}
	else
	{
		try
		{
			MEMW(2, REGF(1));
		}
		catch (int)
		{
			cout << "Нельзя записывать double на место int";
		}
	}
}

void Remote::MOV()
{
	REG(2) = REG(1);
}


void Remote::NOP()
{
	throw - 1;
}