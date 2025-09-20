#include "Reciever.h"

#define REG(x) registers[digit_getter(grid[current_instruction][x])]
#define REGF(x) registers_f[digit_getter(grid[current_instruction][x])]
#define MEM(x) memory[(digit_getter(grid[current_instruction][x])-1000)/4]





Remote::Remote(string** _grid, vector<double> _memory)
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
	case'+':
		res = 1;
		break;
	case'-':
		res =  -1;
		break;
	default:
		res = 0;
		break;
	}
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
	if (r2 == 0) return; // дл€ защиты от аболтусов
	REG(3) = REG(1) / REG(2);
	REG(4) = REG(1) % REG(2);
}

void Remote::FDIV()
{
	if (REGF(2) == 0) return; // дл€ защиты от аболтусов
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
	// заполн€ем нул€ми справа. сдвигаем R1 на R2, записываем в R3
	// использую if дл€ защиты от UBR
	if ((REG(2) >= (sizeof(int) * 8)) || (REG(2) < 0)) return;
	REG(3) = REG(1) << REG(2);

}

void Remote::CMP()
{
	if (REG(1) == REG(2)) {
		this->flag = 0;
	}
	else if (REG(1) <= REG(2)) { // начина€ с этого услови€ и ниже flag попадает также под JNE
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
	// ѕоскольку переход безусловный, мы передаЄм абсолютное значение указател€ на инструкцию
	auto p = grid[current_instruction][1];
	if (jmp_address_detection(p) != 0) return;
	int addr = digit_getter(p);
	this->current_instruction = (addr / 4 - 1);
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
	if (this->flag == 0) return; // нужно узнать как ведЄт себ€ jne при пустом флаге
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
	// проверить первую букву регистра
	if (grid[current_instruction][2][0] == 'r')
	{
		REG(2) = MEM(1);
	}
	else
	{
		REGF(2) = MEM(1);
	}
}

void Remote::ST()
{
	if (grid[current_instruction][1][0] == 'r')
	{
		MEM(2) = REG(1);
	}
	else
	{
		MEM(2) = REGF(1);
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