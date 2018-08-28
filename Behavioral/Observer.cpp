#include <iostream>
#include <vector>
using namespace std;

//abstract observer
class Observer
{
private:
	int valueObs;
public:
	Observer(int _v)
	{
		this->valueObs = _v;
	}

	virtual void update() = 0;

	int getValObs()
	{
		return this->valueObs;
	}
};


class Subject
{
private:
	vector<Observer*> observers;
	int value;//for this task
public:
	void attach(Observer* obs)//add new concrete observer
	{
		observers.push_back(obs);
	}

	void detach(Observer* obs)//remove concrete observer
	{
		auto it = find(observers.begin(), observers.end(), obs);
		if (it != observers.end())
		{
			observers.erase(it);
		}
	}

	void setValue(int _v)
	{
		this->value = _v;
		notify();
	}

	void notify()//notify concrete observers about changes(update)
	{
		for (auto i = observers.begin(); i != observers.end(); i++)
		{
			(*i)->update();
		}
	}

	int getValue()
	{
		return value;
	}
};

//concrete observers
class OneObserver : public Observer
{
private:
	Subject * model;
public:
	OneObserver(Subject* _model, int _v) : Observer(_v)
	{
		this->model = _model;

		model->attach(this);
	}

	void update()
	{
		int v = model->getValue();
		int d = getValObs();
		cout << "subject value: " << v << ",one observer value: " << d << endl;
	}
};

class AnotherObserver : public Observer
{
private:
	Subject * model;
public:
	AnotherObserver(Subject* _model, int _v) : Observer(_v)
	{
		this->model = _model;

		model->attach(this);
	}

	void update()
	{
		int v = model->getValue();
		int d = getValObs();
		cout << "subject value: " << v << ",another observer value: " << d << endl;
	}
};

int main()
{
	Subject subj;
	OneObserver obs1(&subj, 4);
	AnotherObserver obs2(&subj, 5);

	subj.setValue(14);

	system("PAUSE");
	return 0;
}