#include<iostream>
using namespace std;

//base , abstract
class PreparingDrink
{
public:
	void boilWater()
	{
		cout << "water boiled, ";
	}

	virtual void fillCupWithSomething() = 0;

	void addSugar()
	{
		cout << "sugar added, ";
	}
	
	virtual void addTopping() = 0;

	void prepareDrink()
	{
		boilWater();
		fillCupWithSomething();
		addSugar();
		addTopping();
	}
};

//concrete
class PreparingTea : public PreparingDrink
{
public:
	void fillCupWithSomething()
	{
		cout << "a bag of tea put, ";
	}
	void addTopping()
	{
		cout << "nothing added" << endl;
	}
};

class PreparingCoffee : public PreparingDrink
{
public:
	void fillCupWithSomething()
	{
		cout << "some coffee put, ";
	}
	void addTopping()
	{
		cout << "milk added" << endl;
	}
};

int main()
{
	PreparingDrink* array[] = { &PreparingTea(), &PreparingCoffee() };

	//PreparingDrink* pr = new PreparingCoffee();// it is the same

	for (int i = 0; i < 2; i++)
	{
		array[i]->prepareDrink();
	}

	system("PAUSE");
	return 0;
}