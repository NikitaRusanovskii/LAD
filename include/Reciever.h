#pragma once

#include <string>
#include <vector>
#include <regex>

using namespace std;






class Reciever // ���������
{
public:
	Reciever() = default;
	~Reciever() = default;
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


class Memory;
class Remote : public Reciever // ���������� ���� ����������
{
	string** grid;
	int current_instruction;
	int* registers;
	double* registers_f;

	Memory* memory;
	
	int flag;
public:
	Remote(string** _grid, Memory* _memory);
	~Remote()
	{
		delete registers;
		delete registers_f;
		delete memory;
	}
	//���������������
	int digit_getter(string s);
	int jmp_address_detection(string token);
	int* getRegisters();
	int& getCurrInst();
	int ld_st_address_converter(string s);


	//��������������
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

	//��������� ��������
	virtual void AND();
	virtual void OR();
	virtual void NOT();
	virtual void XOR();

	//����� ���������� �������
	virtual void SHR();
	virtual void SHL();

	//����������� ��� if while
	virtual void CMP();
	virtual void JMP();
	virtual void JE();
	virtual void JNE();
	virtual void JL();
	virtual void JLE();
	virtual void JG();
	virtual void JGE();
	
	//������ � �������
	virtual void LD();
	virtual void ST();
	virtual void MOV();

	//��������
	virtual void NOP();
};