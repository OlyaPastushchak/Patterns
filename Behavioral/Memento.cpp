#include<iostream>
#include<string>
using namespace std;


#include<iostream>
#include<string>
using namespace std;

//memento(çíèìîê)
class Memento
{
private:
	string state;

	friend class Originator;//The Originator friend class, can access the internal information, but other classes cannot access

	Memento(const string& _state)
	{
		this->state = _state;
	}

	void setState(const string& _state)
	{
		this->state = _state;
	}

	string getState()
	{
		return this->state;
	}
};

//Responsible for creating a memo, Memento, is used to record the moment of its internal state, and can be used to restore the internal state of the memorandum
class Originator
{
private:
	string state;
public:
	Originator() {}
	Originator(const string& _state)
	{
		this->state = _state;
	}

	Memento* createMemento()
	{
		return new Memento(this->state);
	}

	void restoreToMemento(Memento* _memento)
	{
		this->state = _memento->getState();
	}

	string getState()
	{
		return this->state;
	}

	void setState(const string& _state)
	{
		this->state = _state;
	}

	void show()
	{
		cout << this->state << endl;
	}
};

////Responsible for the preservation of the memo Memento, not on the memo content operation or inspection
class Caretaker
{
private:
	Memento * memento;
public:
	Caretaker() {}
	void setMemento(Memento* _memento)
	{
		this->memento = _memento;
	}

	Memento* getMemento()
	{
		return this->memento;
	}
};

int main()
{
	//Initialize the object, state“Old”
	Originator* orig = new Originator("Old");
	orig->show();

	//Establish and maintain Memento
	Caretaker* cTaker = new Caretaker();
	cTaker->setMemento(orig->createMemento());

	//Change state
	orig->setState("New");
	orig->show();

	//Restoration of state
	orig->restoreToMemento(cTaker->getMemento());
	orig->show();

	system("PAUSE");
	return 0;
}
