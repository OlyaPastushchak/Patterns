#include<iostream>
using namespace std;

class State;

//Context
class Machine
{
private:
	State* current;
public:
	void setCurrent(State* s)
	{
		this->current = s;
	}

	void off();

	void on();

	Machine();
};

//state
class State
{
public:
	virtual void on(Machine* m)
	{
		cout << "already on!" << endl;
	}

	virtual void off(Machine* m)
	{
		cout << "already off!" << endl;
	}
};

void Machine::off()
{
	current->off(this);
}

void Machine::on()
{
	current->on(this);
}

//concrete states
class ON : public State
{
public:
	ON()
	{
		cout << "ON" << endl;
	}
	/*~ON()
	{
		cout << "del ON" << endl;
	}*/

	void off(Machine* m);
};

class OFF : public State
{
public:
	OFF()
	{
		cout << "OFF" << endl;
	}
	/*~OFF()
	{
		cout << "del OFF" << endl;
	}*/

	void on(Machine* m)
	{
		cout << "   going from OFF to ON" << endl;
		m->setCurrent(new ON());
		delete this;
	}
};


void ON::off(Machine* m)
{
	cout << "   going from ON to OFF" << endl;
	m->setCurrent(new OFF());
	delete this;
}

Machine::Machine()
{
	current = new OFF();
}

int main()
{
	Machine* machine = new Machine();
	machine->setCurrent(new ON);

	machine->off();
	machine->on();


	system("PAUSE");
	return 0;
}






