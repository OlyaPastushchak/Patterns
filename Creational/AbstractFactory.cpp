//6.	Патерн «Абстрактна фабрика».Уявимо, що воюють дві країни : Ліліпути та Велетні.
//В кожної країни є по три роди військ : піхота, повітряні війська та морські війська.
//Відповідно у кожної країни є військові наступних типів : піхотинець, льотчик та моряк.
//Кожен рід військ кожної з країн воює між собою.Тобто піхотинець із піхотинцем, моряк з моряком і льотчик з льотчиком.
//Сформувати різні роди військ і продемонструвати їх можливості

#include<iostream>
using namespace std;

enum SwordCharacteristics{ LilliputianSwordPower = 1, GiantSwordPower = 4 };
enum ManeuverabilityCharacteristics { GiantManeuverability = 1, LilliputianManeuverability = 3};
enum WarshipSpeedCharacteristics { GiantWarshipSpeed = 2, LilliputianWarshipSpeed = 5};


//abstract classes for warriors
class Infantryman
{
public:
	virtual int getSwordPower() = 0;
	virtual ~Infantryman(){}
};

class Pilot
{
public:
	virtual int getManeuverability() = 0;
	virtual ~Pilot() {}
};

class Sailor
{
public:
	virtual int getWarshipSpeed() = 0;
	virtual ~Sailor() {}
};

//concrete classes for warriors
class LilliputianInfantryman: public Infantryman
{
public:
	virtual int getSwordPower()
	{
		return LilliputianSwordPower;
	}
};

class LilliputianPilot: public Pilot
{
public:
	virtual int getManeuverability()
	{
		return LilliputianManeuverability;
	}
};

class LilliputianSailor: public Sailor
{
public:
	virtual int getWarshipSpeed()
	{
		return LilliputianWarshipSpeed;
	}
};


class GiantInfantryman : public Infantryman
{
public:
	virtual int getSwordPower()
	{
		return GiantSwordPower;
	}
};

class GiantPilot : public Pilot
{
public:
	virtual int getManeuverability()
	{
		return GiantManeuverability;
	}
};

class GiantSailor : public Sailor
{
public:
	virtual int getWarshipSpeed()
	{
		return GiantWarshipSpeed;
	}
};

//Abstract factory
class ArmyFactory
{
public:
	virtual Infantryman* createInfantryman() = 0;
	virtual Pilot* createPilot() = 0;
	virtual Sailor* createSailor() = 0;
	virtual ~ArmyFactory() {}
};

//concrete factories
class LilliputianArmyFactory: public ArmyFactory
{
public:
	Infantryman* createInfantryman()
	{
		return new LilliputianInfantryman();
	}
	Pilot* createPilot()
	{
		return new LilliputianPilot();
	}
	Sailor* createSailor()
	{
		return new LilliputianSailor();
	}
};

class GiantArmyFactory : public ArmyFactory
{
public:
	Infantryman* createInfantryman()
	{
		return new GiantInfantryman();
	}
	Pilot* createPilot()
	{
		return new GiantPilot();
	}
	Sailor* createSailor()
	{
		return new GiantSailor();
	}
};

//My functions
void printWinner(int lillPowers, int giaPowers)
{
	if (lillPowers > giaPowers)
	{
		cout << "Lilliputian army won!" << endl;
	}
	else if (lillPowers < giaPowers)
	{
		cout << "Giant army won!" << endl;
	}
	else cout << "A draw! Nobody won." << endl;
}

void goWar(ArmyFactory* lillArmy,  ArmyFactory* giaArmy)
{
	Infantryman* lillInfantryman = lillArmy->createInfantryman();
	Pilot* lillPilot = lillArmy->createPilot();
	Sailor* lillSailor = lillArmy->createSailor();

	Infantryman* giaInfantryman = giaArmy->createInfantryman();
	Pilot* giaPilot = giaArmy->createPilot();
	Sailor* giaSailor = giaArmy->createSailor();

	int countLillInfantrymen, countLillPilots, countLillSailors;
	cout << "Create Lilliputian army.\nEnter number of lilliputian infantrymen, pilots, sailors: ";
	cin >> countLillInfantrymen >> countLillPilots >> countLillSailors;
	int countGiaInfantrymen, countGiaPilots, countGiaSailors;
	cout << "Create Giant army.\nEnter number of giant infantrymen, pilots, sailors: ";
	cin >> countGiaInfantrymen >> countGiaPilots >> countGiaSailors;

	int lillPowers = countLillInfantrymen * lillInfantryman->getSwordPower() + countLillPilots * lillPilot->getManeuverability() + countLillSailors * lillSailor->getWarshipSpeed();
	int giaPowers = countGiaInfantrymen * giaInfantryman->getSwordPower() + countGiaPilots * giaPilot->getManeuverability() + countGiaSailors * giaSailor->getWarshipSpeed();
	
	printWinner(lillPowers, giaPowers);
}

int main()
{
	ArmyFactory* lillArmy = new LilliputianArmyFactory;

	ArmyFactory* giaArmy = new GiantArmyFactory;
	
	goWar(lillArmy, giaArmy);

	system("PAUSE");
	return 0;
}