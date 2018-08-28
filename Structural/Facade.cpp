#include <iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
using namespace std;

int COMPUTER_CODE = 1;
int DESK_CODE = 2;
int SHOES_CODE = 3;

int COMPUTER_PRICE = 5000;
int DESK_PRICE = 1000;
int SHOES_PRICE = 100;

int COMPUTER_PACKAGE_PRICE = 50;
int DESK_PACKAGE_PRICE =10;
int SHOES_PACKAGE_PRICE = 100;

int DELIVERY_BY_NP = 10;
int DELIVERY_TO_HOME = 50;

int ORDER_CODE = 0;

class Tovar
{
public:
	int code;
	int amount;
	string typeOfDelivery;
	string address;
	int phoneNumber;
public:
	Tovar(int _code, int _amount, string _type, string _address, int _number) : code(_code), amount(_amount), typeOfDelivery(_type), address(_address), phoneNumber(_number) {}
	Tovar(int _code) : code(_code) {}
	int calculatePrice()
	{
		int price;
		if (code == COMPUTER_CODE)
		{
			price = COMPUTER_PRICE * amount;
		}
		else if (code == DESK_CODE)
		{
			price = DESK_PRICE * amount;
		}
		else if (code == SHOES_CODE)
		{
			price = SHOES_PRICE * amount;
		}

		return price;
	}

};

bool operator < (const Tovar t1, Tovar t2)
{
	return t1.code < t2.code;
}

//subsystems
class Storage
{
private:
	map<Tovar, int> tovars;
public:
	bool ifExistTovar(int tovarCode, int amount)
	{
		int newCount = tovars.at(Tovar(tovarCode)) - amount;
		if (newCount < 0) return 0;
		else
		{
			tovars.erase(Tovar(tovarCode));
			tovars.insert(make_pair(Tovar(tovarCode), newCount));
			return 1;
		}
	}

	void setStorage(map<Tovar, int> st)
	{
		this->tovars = st;
	}
};

class Package
{
private:
	string type;
public:
	int getPricePackTovar(Tovar tovar)
	{
		if (tovar.code == COMPUTER_CODE)
		{
			this ->type = "packed in middle box";
			return COMPUTER_PACKAGE_PRICE;
		}
		else if (tovar.code == DESK_CODE)
		{
			this->type = "packed in large box";
			return DESK_PACKAGE_PRICE;
		}
		else if (tovar.code == SHOES_CODE)
		{
			this->type = "packed in small box";
			return SHOES_PACKAGE_PRICE;
		}
		else throw invalid_argument("bad code for tovar");
	}

};

class Delivery
{
protected:
	int price;
	int orderCode;
public:
	Delivery() :orderCode(ORDER_CODE++) {}
	virtual void doDelivery(string address, ofstream& file) = 0;

	virtual int getOrderCode()
	{
		return this->orderCode;
	}

	virtual int getPrice()
	{
		return this->price;
	}
};

class DeliveryByNovaPoshta : public Delivery
{
public:
	void doDelivery(string address, ofstream& file)
	{
		this->price = DELIVERY_BY_NP;
		file << " delivered to nova poshta on " << address;
	}
};

class DeliveryToHome: public Delivery
{
public:
	void doDelivery(string address, ofstream& file)
	{
		this->price = DELIVERY_TO_HOME;
		file << " delivered to home on " << address;
	}
};

class Payment
{
public:
	int getTotalPrice(Tovar tovar, int delPrice, Package pack)
	{
		int packPrice = pack.getPricePackTovar(tovar);

		return tovar.calculatePrice() + packPrice + delPrice;
	}
};

class Info
{
public:
	void sendInfo(Tovar tovar, ofstream& file, Storage storage, Package pack, Delivery* delivery, Payment payment)
	{
		if (storage.ifExistTovar(tovar.code, tovar.amount) == false) file << "there is no such tovar in storage";
		else
		{
			if (tovar.typeOfDelivery == "np")delivery = new DeliveryByNovaPoshta;
			else if (tovar.typeOfDelivery == "home") delivery = new DeliveryToHome;
			else throw invalid_argument("bad type of deliivery");

			file << "tovar with code " << tovar.code;
			delivery->doDelivery(tovar.address, file);
			file << ".Your order code is " << delivery->getOrderCode();

			file << ". You have to pay " << payment.getTotalPrice(tovar, delivery->getPrice(), pack);
			file << ". If phone number " << tovar.phoneNumber << " is not yours, ignore it." << endl;
		}
	}
};

//facade
class Facade
{
private:
	Storage storage;
	Package package;
	Delivery* delivery;
	Payment payment;
	Info info;
public:
	void executeOrders(vector<Tovar> orders, ofstream& file)
	{
		for (auto i = orders.begin(); i != orders.end(); i++)
		{
			info.sendInfo((*i), file, storage, package, delivery, payment);
		}
	}

	void fillStorage(ifstream& file)
	{
		if (file.fail()) throw exception("can not open file");

		map<Tovar, int> tovars;
		while (!file.eof())
		{
			int codeOfIt, countOfIt;
			file >> codeOfIt;
			file >> countOfIt;

			tovars.insert(make_pair(Tovar(codeOfIt), countOfIt));
		}
		storage.setStorage(tovars);
	}
};


void input(ifstream& file, vector<Tovar>& orders)
{
	if(file.fail()) throw exception("can not open file");

	while (!file.eof())
	{
		int code;
		int amount;
		string typeOfDelivery;
		string address;
		int phoneNumber;

		file >> code >> amount >> typeOfDelivery >> address >> phoneNumber;

		orders.push_back(Tovar(code, amount, typeOfDelivery, address, phoneNumber));
	}
}

int main()
{
	Facade facade;
	ifstream fileStorage("storage.txt");
	ifstream fileOrders("orders.txt");
	ofstream fileAnswer("answer.txt");
	facade.fillStorage(fileStorage);

	vector<Tovar> orders;
	input(fileOrders, orders);
		
	facade.executeOrders(orders, fileAnswer);

	return 0;
}
