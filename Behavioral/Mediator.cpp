#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Brain;

//abstract collegue
class BodyPart
{
private:
	Brain* mediator;
protected:
	string leftOrRight;
public:
	BodyPart(Brain* _mediator, string what)
	{
		this->mediator = _mediator;
		this->leftOrRight = what;
	}

	virtual void changed();//will be defined after mediator

	virtual void print() = 0;
};

//concrete collegues
class Eye : public BodyPart
{
public:
	Eye(Brain* _mediator, string what) : BodyPart(_mediator, what) {}

	void print()
	{
		cout << this->leftOrRight << " eye  ";
	}
};

class Arm : public BodyPart
{
public:
	Arm(Brain* _mediator, string what) : BodyPart(_mediator, what) {}

	void print()
	{
		cout << this->leftOrRight << " arm  ";
	}
};

class Leg : public BodyPart
{
public:
	Leg(Brain* _mediator, string what) : BodyPart(_mediator, what) {}

	void print()
	{
		cout << this->leftOrRight << " leg  ";
	}
};

enum BodyPartsEnum { LeftEye, RightEye, LeftArm, RightArm, LeftLeg, RightLeg };

//mediator
class Brain
{
private:
	BodyPart* parts[6];
public:
	Brain()
	{
		parts[LeftEye] = new Eye(this, "left");
		parts[RightEye] = new Eye(this, "right");
		parts[LeftArm] = new Arm(this, "left");
		parts[RightArm] = new Arm(this, "right");
		parts[LeftLeg] = new Leg(this, "left");
		parts[RightLeg] = new Leg(this, "right");
	}

	virtual void somethingHappenedToBodyPart(BodyPart* changedBodyPart)
	{
		cout << "Now you can only use your ";
		for (int i = LeftEye; i <= RightLeg; i++)
		{
			if (parts[i] != changedBodyPart)
			{
				parts[i]->print();
			}
		}
		cout << endl;
	}

	void handleEvent(BodyPartsEnum which)
	{
		parts[which]->changed();
	}
};

void BodyPart::changed()
{
	mediator->somethingHappenedToBodyPart(this);
}

int main()
{
	Brain brain;
	
	brain.handleEvent(LeftEye);
	brain.handleEvent(RightLeg);

	system("PAUSE");
	return 0;
}