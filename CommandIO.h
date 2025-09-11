#pragma once

class Reciever;

class Command //интерфейс команд всех
{
protected:
	Reciever* reciever;
public:
	Command(Reciever* _reciever) : reciever(_reciever) {}

	virtual ~Command() = default;

	virtual void execute() = 0;
};