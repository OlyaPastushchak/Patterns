////������� Singleton�.����� � ������� ��� ������� ����������� ������ �� �������� ����� ���������� ������.
////��� ����� ������� �������� ��������� �������, ��� � ���� ����� ���������.���, �� ���� ��������1  ������� ��������� � ���������2,
////�� ��  ���� �� ������� ����� ���� ��������� �������.³������� ��� ��������� ������ ������ ������� ���� ������ ����� ������ �� ��������� �������.
////���� ��� ��������� ��������� ������� �� ������ ������������� ��� � ����� ��� �����, 
////� �� ������� ������ ��� �� � ��� ���������� � ������� �� ���������.
//

#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<algorithm>
#include<vector>
#include<list>
#include<map>
#include<ctime>
#include<iomanip>
#include<chrono>


class PhoneStation
{
private:
	list<string> users;
	PhoneStation() {}
	multimap<string, string> logs;
	const string additionLog;
	const string connectionLog = "successfully connected : ";

	string getDate()
	{
		time_t _tm = time(0);

		return to_string(_tm);
	}

public:

	void connect(string user1, string user2)
	{
		auto it1 = find_if(users.begin(), users.end(), [&](string& item) {return item == user1; });
		auto it2 = find_if(users.begin(), users.end(), [&](string& item) {return item == user2; });
		if (it1 != users.end() && it2 != users.end() && it1 != it2)
		{
			cout << user1 << " successfully connected to " << user2 << "\n";
			logs.insert(make_pair(getDate(), connectionLog + user1 + " , " + user2));
		}
		else
		{
			cout << "connection failed \n";
			logs.insert(make_pair(getDate(), "failed to connect : " + user1 + " , " + user2));
		}
	}

	void addUser(string user)
	{
		users.push_back(user);
		logs.insert(make_pair(getDate(), "added new abonent : " + user));
	}

	PhoneStation* getInstance()
	{
		static PhoneStation* instance = new PhoneStation();
		return instance;
	}

	void showLogs()
	{
		//for each (auto var in logs)
		for(auto var= logs.begin();var!=logs.end();var++)
		{
			cout << (*var).first << " -  " << (*var).second << "\n";
		}
	}
};

class City
{
private:
	PhoneStation * p;
public:
	void ConnectToStation(string user1)
	{
		p = p->getInstance();
		p->addUser(user1);
	}

	void connect(string user1, string user2)
	{
		p->connect(user1, user2);
	}

	void getInfo()
	{
		p->showLogs();
	}
};

int main()
{
	City city;
	city.ConnectToStation("jonh");
	city.ConnectToStation("john");
	city.ConnectToStation("olya");

	city.connect("jonh", "john");
	city.connect("jonh", "olya");

	city.getInfo();
	system("pause");
	return 0;
}