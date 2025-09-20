#pragma once

#include"Reciever.h"


class Command //интерфейс команд всех
{
protected:
	Reciever* reciever;
public:
	Command(Reciever* _reciever);

	virtual ~Command();

	virtual void execute() = 0;
};


class SimpleCommand : public Command
{
private:
	void(Reciever::* instruction) ();
public:

	SimpleCommand(Reciever* r, void(Reciever::* _instruction)());
	~SimpleCommand() = default;
	virtual void execute();
};