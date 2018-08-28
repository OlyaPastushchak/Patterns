#pragma once
enum Prices { EspressoPrice = 30, DarkRoastPrice = 35, HouseBlendPrice = 40, CreamPrice = 10, ChocolatePrice = 15, MilkPrice = 5 };

// base class
class BaseCoffee
{
protected:
	int price;
public:
	virtual void print(ofstream& file) = 0;
	int getPrice()
	{
		return this->price;
	}
};

//main class
class Coffee :public BaseCoffee
{
private:
	string name;
public:
	Coffee(string _name)
	{
		this->name = _name;
		if (this->name == "Espresso")
		{
			this->price = EspressoPrice;
		}
		else if (this->name == "DarkRoast")
		{
			this->price = DarkRoastPrice;
		}
		else if (this->name == "HouseBlend")
		{
			this->price = HouseBlendPrice;
		}
		else throw invalid_argument("Bad data in file");
	}

	void print(ofstream& file)
	{
		file << this->name;
	}
};

//decorator
class Decorator : public BaseCoffee
{
private:
	BaseCoffee * bcoffee;
public:
	Decorator(BaseCoffee* _bcoffee)
	{
		this->bcoffee = _bcoffee;
	}

	void print(ofstream& file)
	{
		this->bcoffee->print(file);
	}
};

//concrete decorators
class CreamDecorator :public Decorator
{
public:
	CreamDecorator(BaseCoffee* _bcoffee) : Decorator(_bcoffee)
	{
		this->price = _bcoffee->getPrice() + CreamPrice;
	}

	void print(ofstream& file)
	{
		Decorator::print(file);
		file << " cream";
	}
};

class ChocolateDecorator : public Decorator
{
public:
	ChocolateDecorator(BaseCoffee* _bcoffee) : Decorator(_bcoffee)
	{
		this->price = _bcoffee->getPrice() + ChocolatePrice;
	}

	void print(ofstream& file)
	{
		Decorator::print(file);
		file << " chocolate";
	}
};

class MilkDecorator : public Decorator
{
public:
	MilkDecorator(BaseCoffee* _bcoffee) : Decorator(_bcoffee)
	{
		this->price = _bcoffee->getPrice() + MilkPrice;
	}

	void print(ofstream& file)
	{
		Decorator::print(file);
		file << " milk";
	}

};
