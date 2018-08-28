#include<iostream>
#include<string>
using namespace std;

class Wheels
{
private:
	string size;
public:
	Wheels() :size("") {};
	Wheels(string _size) : size(_size) {};
	void print()
	{
		cout << size << endl;
	}
};

class Frame
{
private:
	string length;
public:
	Frame() :length("") {};
	Frame(string _length) : length(_length) {};
	void print()
	{
		cout << length << endl;
	}
};

class Engine
{
private:
	string type;
public:
	Engine():type("") {};
	Engine(string _type) : type(_type) {};
	void print()
	{
		cout << type << endl;
	}
};


struct Car//product
{
	Wheels wheels;
	Engine engine;
	Frame frame;

	Car():wheels(),engine(), frame() {};
	Car(Wheels _wheels, Engine _engine, Frame _frame) : wheels(_wheels), engine(_engine), frame(_frame) {};
	void print()
	{
		wheels.print();
		engine.print();
		frame.print();
	}
};


class CarBuilder//builder
{
protected:
	Car* car;
public:
	CarBuilder() :car(new Car()) {}
	~CarBuilder() { delete car; }
	virtual void createWheels() = 0;
	virtual void createFrame() = 0;
	virtual void createEngine() = 0;
	Car* getCar()
	{
		return this->car;
	}
};


class CoupeBuilder :public  CarBuilder//concrete builder
{
public:
	void createWheels() 
	{
		car->wheels = Wheels("small wheels");
	}
	void createFrame() 
	{
		car->frame = Frame("short frame");
	}
	void createEngine()
	{
		car->engine = Engine("Wankel engine");
	}
};


class JeepBuilder :public CarBuilder//concrete builder
{
public:
	void createWheels()
	{
		car->wheels = Wheels("medium wheels");
	}
	void createFrame()
	{
		car->frame = Frame("standart frame");
	}
	void createEngine()
	{
		car->engine = Engine("Two-stroke engine");
	}
};


class TruckBuilder :public CarBuilder//concrete builder
{
public:
	void createWheels()
	{
		car->wheels = Wheels("large wheels");
	}
	void createFrame()
	{
		car->frame = Frame("long frame");
	}
	void createEngine()
	{
		car->engine = Engine("Four-stroke engine");
	}
};


void createCar(CarBuilder& builder)//director
{
	builder.createWheels();
	builder.createFrame();
	builder.createEngine();
}

int main()
{
	CoupeBuilder cpBuilder;
	createCar(cpBuilder);
	cout << "Coupe:" << endl;
	cpBuilder.getCar()->print();

	JeepBuilder jpBuilder;
	createCar(jpBuilder);
	cout << "Jeep:" << endl;
	jpBuilder.getCar()->print();

	TruckBuilder trkBuilder;
	createCar(trkBuilder);
	cout << "Truck:" << endl;
	trkBuilder.getCar()->print();

	system("pause");
	return 0;
}

