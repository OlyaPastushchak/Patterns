//1. Нехай в деякому кафе можна замовити кофейні напитки на основі трьох різних сортів кави(Espresso, DarkRoast, HouseBlend)
//та трьох різних добавок(Cream, Chocolate, Milk).В текстових файлах orders1.txt та orders2.txt 
//задано списки замовлень на напитки(сорт кави і список добавок із зазначенням їх кількості).Зчитати дані в контейнер напитків.
//а) Вивести в файл bills.txt рахунки за напитки : назва напитку, вартість.
//б) Знайти найдорожчий та найдешевший напитки.
//в) Використовуючи асоціативний контейнер утворити список витрат для кожного продукту : назва – кількість.Вивести його у файл.
//2. Реалізувати завдання на основі патерну «Декоратор».

#include <cstdio>
#include<iostream>
#include<string>
#include<fstream>
#include<iterator>
#include<vector>
#include<map>

using namespace std;

#include"Decorator.h"

void input(ifstream& file, vector<BaseCoffee*>& drinks)
{
	if (!file.is_open())
	{
		throw exception("can not open file with data");
	}
	while (!file.eof())
	{
		int countToppings;
		string coffeeName;
		file >> coffeeName;
		file >> countToppings;

		BaseCoffee* bcoffee = new Coffee(coffeeName);
		for (int i = 0; i < countToppings; i++)
		{
			string toppingName;
			file >> toppingName;
			
			if (toppingName == "cream")
			{
				bcoffee = new CreamDecorator(bcoffee);
			}
			else if (toppingName == "chocolate")
			{
				bcoffee = new ChocolateDecorator(bcoffee);
			}
			else if (toppingName == "milk")
			{
				bcoffee = new MilkDecorator(bcoffee);
			}
			else throw invalid_argument("bad data in file");

		}

		drinks.push_back(bcoffee);
	}

}

void printBills(ofstream& file, vector<BaseCoffee*> drinks)
{
	for (auto i = drinks.begin(); i != drinks.end(); i++)
	{
		(*i)->print(file);
		file <<" "<< (*i)->getPrice();
		file << endl;
	}
}

void findMinMaxPrice(ofstream& file, vector<BaseCoffee*> drinks)
{
	int minPrice = drinks[0]->getPrice();
	int maxPrice = drinks[0]->getPrice();
	BaseCoffee* cheapestCoffee = (*drinks.begin());
	BaseCoffee* mostExpCoffee = (*drinks.begin());

	for (auto i = drinks.begin(); i != drinks.end(); i++)
	{
		int currentPrice = (*i)->getPrice();
		if (currentPrice < minPrice)
		{
			minPrice = currentPrice;
			cheapestCoffee = (*i);
		}
		if (currentPrice > maxPrice)
		{
			maxPrice = currentPrice;
			mostExpCoffee = (*i);
		}
	}

	file << "The cheapest drink: ";
	cheapestCoffee->print(file);
	file << "\nIts price: " << minPrice << endl;
	file << "The most expensive drink: ";
	mostExpCoffee->print(file);
	file << "\nIts price: " << maxPrice << endl;
}

void calculateSpendings(fstream& fileData, ofstream& fileAnswers)
{
	map<string, int> spendings;

	int countEspressos = 0;
	int countDarkRoasts = 0;
	int countHouseBlends = 0;
	int countCreams = 0;
	int countChocolates = 0;
	int countMilks = 0;

	while (!fileData.eof())
	{
		int countToppings;
		string coffeeName;
		fileData >> coffeeName;
		if (coffeeName== "Espresso")
		{
			countEspressos++;
		}
		else if (coffeeName == "DarkRoast")
		{
			countDarkRoasts++;
		}
		else if (coffeeName == "HouseBlend")
		{
			countHouseBlends++;
		}

		fileData >> countToppings;

		for (int i = 0; i < countToppings; i++)
		{
			string toppingName;
			fileData >> toppingName;

			if (toppingName == "cream")
			{
				countCreams++;
			}
			else if (toppingName == "chocolate")
			{
				countChocolates++;
			}
			else if (toppingName == "milk")
			{
				countMilks++;
			}
		}
	}
	spendings.insert(make_pair("Espresso", countEspressos));
	spendings.insert(make_pair("DarkRoast", countDarkRoasts));
	spendings.insert(make_pair("HouseBlend", countHouseBlends));
	spendings.insert(make_pair("Cream", countCreams));
	spendings.insert(make_pair("Chocolate", countChocolates));
	spendings.insert(make_pair("Milk", countMilks));

	for (auto i = spendings.begin(); i != spendings.end(); i++)
	{
		fileAnswers << (*i).first << " - " << (*i).second << endl;
	}
}

void makeOneFileFromTwo(ifstream& file1, ifstream& file2, fstream& file)
{
	while (!file1.eof())
	{
		string line;
		getline(file1, line);
		file << line;
		file << endl;
	}
	while (!file2.eof())
	{
		string line;
		getline(file2, line);
		file << line;
		file << endl;
	}		
}


int main()
{	
	try
	{
		ifstream fileOrders1("orders1.txt");
		ifstream fileOrders2("orders2.txt");
		fstream fileAllOrders("allOrders.txt", ios::out | ios::in);
		vector<BaseCoffee*> drinks;
		input(fileOrders1, drinks);
		input(fileOrders2, drinks);

		ofstream fileBills("Bills.txt");
		printBills(fileBills, drinks);

		ofstream fileMinMax("MinMax.txt");
		findMinMaxPrice(fileMinMax, drinks);
		fileOrders1.seekg(0, ios::beg);//again from the beginning of file
		fileOrders2.seekg(0, ios::beg);
		makeOneFileFromTwo(fileOrders1, fileOrders2, fileAllOrders);

		ofstream fileSpendings("Spendings.txt");
		fileAllOrders.seekg(0, ios::beg);
		calculateSpendings(fileAllOrders, fileSpendings);

		fileAllOrders.close();
		remove("allOrders.txt");
		fileMinMax.close();
		fileOrders1.close();
		fileOrders2.close();
		fileBills.close();
	}
	catch (invalid_argument& ex)
	{
		cout << ex.what();
	}
	catch (exception& ex)
	{
		cout << ex.what();
	}

	system("PAUSE");
	return 0;
}















