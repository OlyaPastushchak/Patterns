#include<iostream>
#include<string>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;

class Attributes
{
protected:
	string language;
	string sectionName;
public:
	Attributes() {}
	virtual void printAtt() = 0;
	virtual void read(ifstream& file) = 0;
	virtual string getLanguage()
	{
		return language;
	}
	virtual string getSectionName()
	{
		return sectionName;
	}
};
class TheoryAttributes : public Attributes
{
private:
	string text;
public:
	void printAtt()
	{
		cout << language << sectionName << text << endl;
	}

	void read(ifstream& file)
	{
		file >> language >> sectionName >> text;
	}
};
class TestsAttributes : public Attributes
{
private:
	string compiler;
	string task;
	string path;
public:
	void printAtt()
	{
		cout << language << sectionName << compiler << task << path << endl;
	}

	void read(ifstream& file)
	{
		file >> language >> sectionName >> compiler>>task>>path;
	}
};

//abstract class
class SectionPart
{
protected:
	Attributes* atts;
public:
	virtual void printInfo() = 0;
	SectionPart() {}
	SectionPart(Attributes* _atts) : atts(_atts) {}

	virtual string getLanguage()
	{
		return atts->getLanguage();
	}

	virtual string getSectionName()
	{
		return atts->getSectionName();
	}
};

//concrete classes
class Theory : public SectionPart
{
public:
	void printInfo()
	{
		atts->printAtt();
	}
	Theory() :SectionPart() {}
	Theory(Attributes* _atts) : SectionPart(atts) {}

};

class Tests : public SectionPart
{
public:
	void printInfo()
	{
		atts->printAtt();
	}
	Tests() :SectionPart() {}
	Tests(Attributes* _atts) : SectionPart(atts){}
};

//abstract factory
class SectionPartFactory
{
public:
	//factory method
	virtual SectionPart* createSectionPart(Attributes* atts) = 0;
	virtual ~SectionPartFactory() {}
};

//concrete factories
class TheoryFactory : public SectionPartFactory
{
public:
	SectionPart * createSectionPart(Attributes* atts)
	{
		return new Theory(atts);
	}
};

class TestsFactory : public SectionPartFactory
{
public:
	SectionPart * createSectionPart(Attributes* atts)
	{
		return new Tests(atts);
	}
};

class Section
{
private:
	SectionPart * theoryPart;
	SectionPart* testsPart;
public:
	Section(SectionPart* th, SectionPart* te) : theoryPart(th), testsPart(te) {}
};

void input(ifstream& file, vector<SectionPart*>& sectionPartsVector,SectionPartFactory* factory, string type)
{
	if (file.fail()) throw exception("problems with files");
	while (!file.eof())
	{
		Attributes* atts;
		if(type == "theory") atts = new TheoryAttributes;
		else atts = new TestsAttributes;

		atts->read(file);

		SectionPart* part = factory->createSectionPart(atts);
		sectionPartsVector.push_back(part);
	}
}

vector<Section> makeSections(vector<SectionPart*> theoryPartsVector, vector<SectionPart*> testsPartsVector)
{
	vector<Section> sections;
	for (auto itOnTheory = theoryPartsVector.begin(); itOnTheory != theoryPartsVector.end(); itOnTheory++)
	{
		for (auto itOnTests = testsPartsVector.begin(); itOnTheory != testsPartsVector.end(); itOnTests++)
		{
			if ((*itOnTheory)->getLanguage() == (*itOnTests)->getLanguage() && (*itOnTheory)->getSectionName() == (*itOnTests)->getSectionName())
			{
				sections.push_back(Section((*itOnTheory), (*itOnTests)));
			}
		}
		/*if (itOnTests == testsPartsVector.end())
		{
			throw invalid_argument("bad data in file");
		}
		else
		{
			sections.push_back(Section((*itOnTheory), (*itOnTests)));
		}*/
	}

	return sections;
}

int main()
{
	SectionPartFactory* theoryFactory = new TheoryFactory;
	SectionPartFactory* testsFactory = new TestsFactory;

	vector<SectionPart*> theoryPartsVector;
	vector<SectionPart*> testsPartsVector;
	ifstream fileTheory("theory.txt");
	ifstream fileTests("tests.txt");

	input(fileTheory, theoryPartsVector, theoryFactory, "theory");
	input(fileTests, testsPartsVector, testsFactory, "tests");

	vector<Section> sections = makeSections(theoryPartsVector, testsPartsVector);

	return 0;
}







