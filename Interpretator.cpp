#include "Interpretator.h"
#include"Commands.h"
#include"Reciever.h"

Interpretator::Interpretator(string** _grid, vector<double> _memory)
{
	grid = _grid;
	memory = _memory;
	remote = new Remote(grid, memory);




	instructions["add"] = new ADD(remote);
	instructions["sub"] = new SUB(remote);
	instructions["nop"] = new NOP(remote);
	instructions["fadd"] = new FADD(remote);
	instructions["fsub"] = new FSUB(remote);
	instructions["mul"] = new MUL(remote);
	instructions["fmul"] = new FMUL(remote);
	instructions["div"] = new DIV(remote);
	instructions["fdiv"] = new FDIV(remote);
	instructions["and"] = new AND(remote);
	instructions["or"] = new OR(remote);
	instructions["not"] = new NOT(remote);
	instructions["xor"] = new XOR(remote);
	instructions["inc"] = new INC(remote);
	instructions["dec"] = new DEC(remote);
	instructions["cmp"] = new CMP(remote);
	instructions["shl"] = new SHL(remote);
	instructions["shr"] = new SHR(remote);
	instructions["jmp"] = new JMP(remote);
	instructions["je"] = new JE(remote);
	instructions["jne"] = new JNE(remote);
	instructions["jl"] = new JL(remote);
	instructions["jle"] = new JLE(remote);
	instructions["jg"] = new JGE(remote);
	instructions["ld"] = new LD(remote);
	instructions["st"] = new ST(remote);
	instructions["mov"] = new MOV(remote);

}//в сигнатуре все что и у ремоута

void Interpretator::executeCommand()
{
	if (com != nullptr)
	{
		com->execute();
	}
	//обработку можно сделать
}

void Interpretator::setCommand(Command* _com)
{
	if (com != _com)
	{
		com = _com; //поверхностно указатель копируем
	}
}


void Interpretator::Interpretate()
{
	try
	{
		while (true)
		{
			string s = grid[remote->getCurrInst()][0];
			setCommand(instructions[s]);
			executeCommand();
			remote->getCurrInst()++;
		}
	}
	catch (int)
	{
		cout << remote->getRegisters()[3] << endl;

	}
}