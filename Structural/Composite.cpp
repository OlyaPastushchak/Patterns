//Патерн Composite.Розробити структуру класів для представлення каталогу товарів деякого супермаркету.
//Передбачається, що каталог може мати деревовидну структуру із довільною глибиною вкладеності категорій товарів.
//Кінцевий товар містить ціну та ІD.
//Програма повинна зчитати дані про категорії та товари, а також видрукувати каталог у файл у розгорнутому вигляді.

#include <iostream>
#include<string>
#include<map>
#include<fstream>
#include<vector>
using namespace std;

//component
class Component
{
public:
	virtual void print(ofstream& file) = 0;
	virtual ~Component() {}
};

//primitive
class Tovar : public Component
{
private:
	string name;
	int id;
public:
	Tovar(string _name, int _id) : name(_name), id(_id) {}
	void print(ofstream& file)
	{
		file << name << " " << id << endl;
	}
};

//composite
class Composite : public Component // cathegory
{
private:
	vector<Component*> units;
public:
	void print(ofstream& file)
	{
		for (int i = 0; i < this->units.size(); i++)
		{
			units[i]->print(file);
		}
	}

	void addUnit(Component* unit)
	{
		units.push_back(unit);
	}
};

void input(ifstream& file, multimap<string, pair<string, int>>& tovars)
{

}

int main()
{
	ifstream fileData("Data.txt");
	multimap<string, pair<string, int>> tovars;//cathegory - 



	/*Composite containers[4];

	ofstream file("Answer.txt");

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++)
			containers[i].addUnit(new Tovar("Milk", 2));

	for (int i = 1; i < 4; i++)
		containers[0].addUnit(&(containers[i]));

	for (int i = 0; i < 4; i++)
	{
		containers[i].print(file);
		cout << endl;
	}*/
	return 0;
}
