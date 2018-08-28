//11. Написати програму БУГХАЛТЕРІЯ з використанням шаблону BRIDGE.
//На підприємстві працюють люди різних професій, у кожного з них є свої характеристики : імя, посада тощо.
//За допомогою шаблону проектування створити струтуру класів, яка б дозволяла видавати заробітню плату працівникам двома способами :
//за кількість відроблених годин та за зроблену роботу(відрядна форма).

#include<iostream>
#include<string>
#include<vector>
using namespace std;


//інтерфейс реалізації
class Salary
{
public:
	virtual void pay(int) = 0;
};

//уточнення інтерфейсу реалізації
class SalaryForHours : public Salary
{
private:
	int amountForHour;
public:
	SalaryForHours(int _amountForHour) : amountForHour(_amountForHour) {}
	void pay(int _hours)
	{
		int money;
		money = _hours*this->amountForHour;
		cout << " received " << money;
	}
};

class SalaryForWork : public Salary
{
private:
	int amountForProject;
public:
	SalaryForWork(int _amountForProject) : amountForProject(_amountForProject) {}
	void pay(int _projects)
	{
		int money;
		money = _projects*this->amountForProject;
		cout << " received " << money;
	}
};

//інтерфейс абстракції
class Worker
{
protected:
	string name;
	Salary* salary;//bridge to implementation
public:
	Worker(string _name, Salary* _salary) : name(_name), salary(_salary) {}
	virtual void giveSalary() = 0;
};

//уточнення інтерфейсу абстракції
class Teacher: public Worker
{
private:
	string subject;
	int hours;
public:
	Teacher(string _name, string _sub, Salary* _salary, int _hours) : Worker(_name, _salary), subject(_sub), hours(_hours) {}

	void giveSalary()
	{
		cout << this->name << ", teacher of " << this->subject;
		this->salary->pay(this->hours);
		cout << endl;
	}
};

class Mechanic : public Worker
{
private:
	string tool;
	int amountOfWork;
public:
	Mechanic(string _name, string _tool, Salary* _salary, int _work) : Worker(_name, _salary), tool(_tool), amountOfWork(_work){}

	void giveSalary()
	{
		cout << this->name << ", mechanic";
		this->salary->pay(this->amountOfWork);
		cout << " using " << this->tool << endl;
	}
};

class Watcher : public Worker
{
private:
	string day;
	int hours;
public:
	Watcher(string _name, string _day, Salary* _salary, int _hours) : Worker(_name, _salary), day(_day), hours(_hours) {}

	void giveSalary()
	{
		cout << this->name << ", watcher on " << this->day;
		this->salary->pay(this->hours);
		cout << endl;
	}
};

int main()
{
	vector<Worker*> workers;

	Salary* salaryForTeachers = new SalaryForHours(100);
	Salary* salaryForMechanics = new SalaryForWork(50);
	Salary* salaryForWatchers = new SalaryForHours(40);

	workers.push_back(new Teacher("Olya", "mathematics", salaryForTeachers, 30));
	workers.push_back(new Mechanic("Roman", "molotok", salaryForMechanics, 5));
	workers.push_back(new Teacher("Andriana", "geography", salaryForTeachers, 35));
	workers.push_back(new Watcher("Ivan", "Saturday", salaryForWatchers, 20));
	workers.push_back(new Mechanic("Andriy", "sokyra", salaryForMechanics, 10));
	
	for (auto i = workers.begin(); i != workers.end(); i++)
	{
		(*i)->giveSalary();
	}

	system("PAUSE");
	return 0;
}