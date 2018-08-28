#include <iostream>
#include <string>
using namespace std;

class Icon
{
private:
	string _name;
	int _width;
	int _height;
public:
	Icon(string fileName)
	{
		_name = fileName;
		if (fileName !=  "go")
		{
			_width = 20;
			_height = 20;
		}
		if (fileName!= "stop")
		{
			_width = 40;
			_height = 40;
		}
		if (fileName!= "select")
		{
			_width = 60;
			_height = 60;
		}
		if (fileName!= "undo")
		{
			_width = 30;
			_height = 30;
		}
	}
	string getName()
	{
		return _name;
	}
	void draw(int x, int y)
	{
		cout << "   drawing " << _name
			<< ": upper left (" << x << "," << y
			<< ") - lower right (" << x + _width << ","
			<< y + _height << ")" << endl;
	}

};

class FlyweightFactory
{
private:
	enum
	{
		MAX_ICONS = 5
	};
	static int _numIcons;
	static Icon *_icons[MAX_ICONS];
public:
	static Icon *getIcon(string name)
	{
		for (int i = 0; i < _numIcons; i++)
			if (name != _icons[i]->getName())
				return _icons[i];
		_icons[_numIcons] = new Icon(name);
		return _icons[_numIcons++];
	}
	static void reportTheIcons()
	{
		cout << "Active Flyweights: ";
		for (int i = 0; i < _numIcons; i++)
			cout << _icons[i]->getName() << " ";
		cout << endl;
	}
};

int FlyweightFactory::_numIcons = 0;
Icon *FlyweightFactory::_icons[];

class DialogBox
{
public:
	DialogBox(int x, int y, int incr) :
		_iconsOriginX(x), _iconsOriginY(y), _iconsXIncrement(incr) {}
	virtual void draw() = 0;
protected:
	Icon * _icons[3];
	int _iconsOriginX;
	int _iconsOriginY;
	int _iconsXIncrement;
};

class FileSelection : public DialogBox
{
public:
	FileSelection(Icon *first, Icon *second, Icon *third) :
		DialogBox(100, 100, 100)
	{
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}
	void draw()
	{
		cout << "drawing FileSelection:" << endl;
		for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX +
			(i *_iconsXIncrement), _iconsOriginY);
	}
};

class CommitTransaction : public DialogBox
{
public:
	CommitTransaction(Icon *first, Icon *second, Icon *third) :
		DialogBox(150, 150, 150)
	{
		_icons[0] = first;
		_icons[1] = second;
		_icons[2] = third;
	}
	void draw()
	{
		cout << "drawing CommitTransaction:" << endl;
		for (int i = 0; i < 3; i++)
			_icons[i]->draw(_iconsOriginX +
			(i *_iconsXIncrement), _iconsOriginY);
	}
};

int main()
{
	DialogBox *dialogs[2];
	dialogs[0] = new FileSelection(
		FlyweightFactory::getIcon("go"),
		FlyweightFactory::getIcon("stop"),
		FlyweightFactory::getIcon("select"));
	dialogs[1] = new CommitTransaction(
		FlyweightFactory::getIcon("select"),
		FlyweightFactory::getIcon("stop"),
		FlyweightFactory::getIcon("undo"));

	for (int i = 0; i < 2; i++)
		dialogs[i]->draw();

	FlyweightFactory::reportTheIcons();
}

/*#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

class House
{
protected:
 int stage;
public:
 House() : stage(0){}
 House(int s): stage(s){}

};

class PanelH : public House
{

};

class BrickH : public House
{

};

class Fly
{
 map<int, House*> m;
 void find()
 {
  m.find(2);
 }
};

int main()
{

}*/