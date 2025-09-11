#pragma once

#include <string>
#include <vector>
using namespace std;



class Reciever // интерфейс
{
public:
	Reciever() = default;
	virtual void ADD() = 0;
	virtual void SUB() = 0;
	virtual void FADD() = 0;
	virtual void FSUB() = 0;
	virtual void MUL() = 0;
	virtual void FMUL() = 0;
	virtual void DIV() = 0;
	virtual void FDIV() = 0;
	virtual void AND() = 0;
	virtual void OR() = 0;
	virtual void NOT() = 0;
	virtual void XOR() = 0;
	virtual void INC() = 0;
	virtual void DEC() = 0;
	virtual void CMP() = 0;
	virtual void SHL() = 0;
	virtual void SHR() = 0;
	virtual void JMP() = 0;
	virtual void JE() = 0;
	virtual void JNE() = 0;
	virtual void JL() = 0;
	virtual void JLE() = 0;
	virtual void JG() = 0;
	virtual void JGE() = 0;
	virtual void LD() = 0;
	virtual void ST() = 0;
	virtual void MOV() = 0;
	virtual void NOP() = 0;

};



class Remote : public Reciever // реализатор всех инструкций
{
	string** grid;
	int current_instruction;
	int* registers;
	double* registers_f;

	vector<double> memory;
	string flag;

public:
	Remote(string** _grid, vector<double> _memory);
	~Remote()
	{
		//позже
	}
	//вспомогательные
	int digit_getter(string s);
	int jmp_address_detection(string token);
	int* getRegisters();
	int& getCurrInst();


	//арифметические
	virtual void ADD();
	virtual void FADD();
	virtual void SUB();
	virtual void FSUB();
	virtual void MUL();
	virtual void FMUL();
	virtual void DIV();
	virtual void FDIV();
	virtual void INC();
	virtual void DEC();

	//побитовые операции
	virtual void AND();
	virtual void OR();
	virtual void NOT();
	virtual void XOR();

	//вроде логические сдивиги
	virtual void SHR();
	virtual void SHL();

	//конструкции для if while
	virtual void CMP();
	virtual void JMP();
	virtual void JE();
	virtual void JNE();
	virtual void JL();
	virtual void JLE();
	virtual void JG();
	virtual void JGE();
	
	//работа с памятью
	virtual void LD();
	virtual void ST();
	virtual void MOV();

	//конечная
	virtual void NOP();
};