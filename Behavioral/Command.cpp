#include<iostream>
using namespace std;

//abstract Command
class Command
{
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
};

//receiver
class TV
{
public:
	void turnOn()
	{
		cout << "TV turned ON" << endl;
	}

	void turnOff()
	{
		cout << "TV turned OFF" << endl;
	}
};

//concrete commands
class TVOnCommand : public Command
{
private:
	TV* tv;
public:
	TVOnCommand(TV* _tv): tv(_tv) {}

	void execute()
	{
		tv->turnOn();
	}

	void undo()
	{
		tv->turnOff();
	}
};

//invoker(звертається до команди, ініціатор)
class Pult
{
private:
	Command* command;
public:
	Pult() {}

	void setCommand(Command* _c)
	{
		this->command = _c;
	}

	void pressButton()
	{
		command->execute();
	}

	void pressUndo()
	{
		command->undo();
	}
};

int main()
{
	Pult* pult = new Pult();
	TV* tv = new TV();

	pult->setCommand(new TVOnCommand(tv));
	pult->pressButton();
	pult->pressUndo();

	/*Invoker* invoker = new Invoker();
	Receiver* receiver = new Receiver();
	ConcreteCommand command = new ConcreteCommand(receiver);
	invoker.SetCommand(command);
	invoker.Run();*/

	system("PAUSE");
	return 0;
}
