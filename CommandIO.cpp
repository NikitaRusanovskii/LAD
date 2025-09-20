#include "CommandIO.h"
#include"Reciever.h"
Command::Command(Reciever* _reciever) : reciever(_reciever) {}

Command::~Command()
{
	delete reciever;
}



SimpleCommand::SimpleCommand(Reciever* r, void(Reciever::* _instruction)()) :
	Command(r) {
	instruction = _instruction;
}
void SimpleCommand::execute()
{
	(reciever->*instruction)();
}