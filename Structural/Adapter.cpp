#include<iostream>
using namespace std;

const double CURRENT_FAHRENHEIT_TEMPERATURE = 41.0;

double convertFahrToCelsius(double fTemperature)
{
	double cTemperture = (fTemperature - 32.0)*(5.0 / 9.0);

	return cTemperture;
}


class FahrenheitThermometer
{
public:
	virtual double getFahrenheitTemperature() = 0;
};

class FahrenheitSensor :public FahrenheitThermometer//adaptee
{
public:
	double getFahrenheitTemperature()
	{
		return CURRENT_FAHRENHEIT_TEMPERATURE;
	}
};

class CelsiusThermometr//target
{
public:
	virtual void getCelsiusTemperature() = 0;
};

class CelsiusSensor : public CelsiusThermometr
{
public:
	void getCelsiusTemperature()
	{
		cout << "Temperature in Celsius scale: ";
	}
};

class Client
{
public:
	void discoverTemperature(CelsiusThermometr* thermometr)
	{
		thermometr->getCelsiusTemperature();
	}
};

class Adapter : public CelsiusThermometr
{
private:
	FahrenheitSensor*  fSensor;
public:
	Adapter(FahrenheitSensor* fSensor)
	{
		this->fSensor = fSensor;
	}

	void getCelsiusTemperature()
	{
		double cTemperature = convertFahrToCelsius(this->fSensor->getFahrenheitTemperature());

		cout << cTemperature << " degrees" << endl;
	}

	~Adapter()
	{
		delete this->fSensor;
	}
};


int main()
{
	Client client;

	CelsiusSensor* sensor = new CelsiusSensor();
	client.discoverTemperature(sensor);

	CelsiusThermometr* adapter = new Adapter(new FahrenheitSensor());
	adapter->getCelsiusTemperature();

	system("pause");
	return 0;
}
