#pragma once

class Reciever;

class Command //��������� ������ ����
{
protected:
	Reciever* reciever;
public:
	Command(Reciever* _reciever) : reciever(_reciever) {}

	virtual ~Command() = default;

	virtual void execute() = 0;
};