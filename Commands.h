#pragma once

#include"CommandIO.h"

////
///// Позже укорочу все, пока работает так
///


class ADD : public Command
{
public:
	ADD(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class SUB : public Command
{
public:
	SUB(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class FADD : public Command
{
public:
	FADD(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class FSUB : public Command
{
public:
	FSUB(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class MUL : public Command
{
public:
	MUL(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class FMUL : public Command
{
public:
	FMUL(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class DIV : public Command
{
public:
	DIV(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class FDIV : public Command
{
public:
	FDIV(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class  AND : public Command
{
public:
	AND(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class OR : public Command
{
public:
	OR(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class NOT : public Command
{
public:
	NOT(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class SHR : public Command
{
public:
	SHR(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class SHL : public Command
{
public:
	SHL(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class CMP : public Command
{
public:
	CMP(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class INC : public Command
{
public:
	INC(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class DEC : public Command
{
public:
	DEC(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class XOR : public Command
{
public:
	XOR(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class JE : public Command
{
public:
	JE(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class JMP : public Command
{
public:
	JMP(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};


class JNE : public Command
{
public:
	JNE(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};


class JL : public Command
{
public:
	JL(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};


class JLE : public Command
{
public:
	JLE(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};


class JG : public Command
{
public:
	JG(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class JGE : public Command
{
public:
	JGE(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class LD : public Command
{
public:
	LD(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class ST : public Command
{
public:
	ST(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};

class MOV : public Command
{
public:
	MOV(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};



class NOP : public Command
{
public:
	NOP(Reciever* _reciever) : Command(_reciever) {}
	virtual void execute();
};