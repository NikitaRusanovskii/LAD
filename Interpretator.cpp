#include "Interpretator.h"
#include"CommandIO.h"
#include"Reciever.h"

#define MAX_ITERS 700

Interpretator::Interpretator(int _n, string** _grid, vector<double> _memory)
{
	n = _n;
	iter = 0;
	grid = _grid;
	memory = _memory;
	remote = new Remote(grid, memory);




	instructions["add"] = new SimpleCommand(remote, &Reciever::ADD);
	instructions["sub"] = new SimpleCommand(remote, &Reciever::SUB);
	instructions["nop"] = new SimpleCommand(remote, &Reciever::NOP);
	instructions["fadd"] = new SimpleCommand(remote, &Reciever::FADD);
	instructions["fsub"] = new SimpleCommand(remote, &Reciever::FSUB);
	instructions["mul"] = new SimpleCommand(remote, &Reciever::MUL);
	instructions["fmul"] = new SimpleCommand(remote, &Reciever::FMUL);
	instructions["div"] = new SimpleCommand(remote, &Reciever::DIV);
	instructions["fdiv"] = new SimpleCommand(remote, &Reciever::FDIV);
	instructions["and"] = new SimpleCommand(remote, &Reciever::AND);
	instructions["or"] = new SimpleCommand(remote, &Reciever::OR);
	instructions["not"] = new SimpleCommand(remote, &Reciever::NOT);
	instructions["xor"] = new SimpleCommand(remote, &Reciever::XOR);
	instructions["inc"] = new SimpleCommand(remote, &Reciever::INC);
	instructions["dec"] = new SimpleCommand(remote, &Reciever::DEC);
	instructions["cmp"] = new SimpleCommand(remote, &Reciever::CMP);
	instructions["shl"] = new SimpleCommand(remote, &Reciever::SHL);
	instructions["shr"] = new SimpleCommand(remote, &Reciever::SHR);
	instructions["jmp"] = new SimpleCommand(remote, &Reciever::JMP);
	instructions["je"] = new SimpleCommand(remote, &Reciever::JE);
	instructions["jne"] = new SimpleCommand(remote, &Reciever::JNE);
	instructions["jl"] = new SimpleCommand(remote, &Reciever::JL);
	instructions["jle"] = new SimpleCommand(remote, &Reciever::JLE);
	instructions["jg"] = new SimpleCommand(remote, &Reciever::JG);
	instructions["ld"] = new SimpleCommand(remote, &Reciever::LD);
	instructions["st"] = new SimpleCommand(remote, &Reciever::ST);
	instructions["mov"] = new SimpleCommand(remote, &Reciever::MOV);

}//в сигнатуре все что и у ремоута

Interpretator::~Interpretator()
{
	if (com != nullptr)
	{
		delete com;
	}
	delete remote;

	for (int i = 0; i < n; i++)
	{
		delete grid[i];
	}

	//grid будет удалятся в remote

	delete instructions["add"];
	delete instructions["sub"];
	delete instructions["nop"];
	delete instructions["fadd"];
	delete instructions["fsub"];
	delete instructions["mul"];
	delete instructions["fmul"];
	delete instructions["div"];
	delete instructions["fdiv"];
	delete instructions["and"];
	delete instructions["or"];
	delete instructions["not"];
	delete instructions["xor"];
	delete instructions["inc"];
	delete instructions["dec"];
	delete instructions["cmp"];
	delete instructions["shl"];
	delete instructions["shr"];
	delete instructions["jmp"];
	delete instructions["je"];
	delete instructions["jne"];
	delete instructions["jl"];
	delete instructions["jle"];
	delete instructions["jg"];
	delete instructions["ld"];
	delete instructions["st"];
	delete instructions["mov"];
}


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
		while(remote->getCurrInst() < n && iter < MAX_ITERS)
		{
			string s = grid[remote->getCurrInst()][0];
			setCommand(instructions[s]);
			executeCommand();
			remote->getCurrInst()++;
			iter++;
		}
		cout << "Ended without nop";
	}
	catch (int)
	{
		cout << "NOP";
	}
}