//7.	Патерн “Прототип”.Розробити програму для утворення екзаменаційної відомості :
//студенти - оцінки певної групи, предмет, викладач.Передбачити можливість клонування відомостей, та метод очищення даних про оцінки,
//зміну предмета та зміна викладача.
//Передбачити пул відомостей за групами, з якого можна брати відомості і клонувати для інших предметів

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
#include<string>
using namespace std;

//Prototype , abstract
class INote
{
public:
	virtual INote* clone() = 0;
	virtual void getInfo() = 0;
	virtual void deleteMarks() = 0;
	virtual void changeSubject(string) = 0;
	virtual void changeLecturer(string) = 0;
	virtual void setData(ifstream&) = 0;
	virtual int getStudentsQuantity() = 0;
};

//concrete
class Note:public INote
{
private:
	vector<int> marks;
	string lecturer;
	string subject;
public:
	Note() : marks(0), lecturer(""), subject("") {}
	Note(vector<int> m, string l, string s) :marks(m), lecturer(l), subject(s) {}
	Note(int m, string l, string s) :lecturer(l), subject(s)
	{
		marks.push_back(m);
	}
	Note(Note& note)
	{
		this->subject = note.subject;
		this->lecturer = note.lecturer;
		this->marks.clear();
		this->marks.swap(note.marks);
	}

	void getInfo()
	{
		cout << "subject : " << this->subject << "\n";
		cout << "lecturer : " << this->lecturer << "\n";
		cout << "group list :\n";
		for (auto i = marks.begin(); i != marks.end(); i++)
		{
			cout << (*i) << endl;
		}
	}

	void deleteMarks()
	{
		marks.erase(marks.begin(), marks.end());
	}

	void changeSubject(string newSubject)
	{
		this->subject = newSubject;
	}

	void changeLecturer(string newLecturer)
	{
		this->lecturer = newLecturer;
	}

	INote* clone()
	{
		return new Note(this->marks, this->lecturer, this->subject);
	}

	void setData(ifstream& file)
	{
		file >> this->subject;
		file >> this->lecturer;
		int amountOfStudents;
		int mark;
		file >> amountOfStudents;
		for (int i = 0; i < amountOfStudents; i++)
		{
			file >> mark;
			marks.push_back(mark);
		}
	}

	int getStudentsQuantity()
	{
		return this->marks.size();
	}
};

//storage
vector<Note*> NOTES;

void input(ifstream& file)
{
	if (!file.is_open())
	{
		throw fstream::failure("can not create pull from file\n");
	}
	Note* tmp = new Note();
	while (!file.eof())
	{
		//if(dynamic_cast<Note*>(tmp))
		tmp->setData(file);
		NOTES.push_back(tmp);
		tmp = new Note();
	}
	delete tmp;
}

Note* getNoteByCode(int code)
{
	if (code < 0)
	{
		throw invalid_argument("invalid group number");
	}

	auto it = find_if(NOTES.begin(), NOTES.end(), [&](INote* item) {return item->getStudentsQuantity() == code; });

	return new Note(**it);
}

int main()
{


	return 0;
}

