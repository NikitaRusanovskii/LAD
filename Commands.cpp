#include "Commands.h"
#include"Reciever.h"

void ADD::execute()
{
	reciever->ADD();
}
void SUB::execute()
{
	reciever->SUB();
}
void MUL::execute()
{
	reciever->MUL();
}
void DIV::execute()
{
	reciever->DIV();
}
void FADD::execute()
{
	reciever->FADD();
}
void FSUB::execute()
{
	reciever->FSUB();
}
void FMUL::execute()
{
	reciever->FMUL();
}
void FDIV::execute()
{
	reciever->FDIV();
}
void AND::execute()
{
	reciever->AND();
}
void OR::execute()
{
	reciever->OR();
}
void XOR::execute()
{
	reciever->XOR();
}
void NOT::execute()
{
	reciever->NOT();
}
void SHL::execute()
{
	reciever->SHL();
}
void SHR::execute()
{
	reciever->SHR();
}
void CMP::execute()
{
	reciever->CMP();
}
void JMP::execute()
{
	reciever->JMP();
}
void JE::execute()
{
	reciever->JE();
}
void JNE::execute()
{
	reciever->JNE();
}
void JL::execute()
{
	reciever->JL();
}
void JLE::execute()
{
	reciever->JLE();
}
void JG::execute()
{
	reciever->JG();
}
void JGE::execute()
{
	reciever->JGE();
}
void LD::execute()
{
	reciever->LD();
}
void ST::execute()
{
	reciever->ST();
}
void MOV::execute()
{
	reciever->MOV();
}
void NOP::execute()
{
	reciever->NOP();
}
void INC::execute()
{
	reciever->INC();
}
void DEC::execute()
{
	reciever->DEC();
}