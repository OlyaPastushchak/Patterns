#include<iostream>
using namespace std;

//abstract handler
class Handler
{
protected:
	Handler* nextHandler;
public:
	Handler() :nextHandler(NULL) {}

	virtual void handleRequest(int value) = 0;

	void setNextHandler(Handler* _nextInLine)
	{
		this->nextHandler = _nextInLine;
	}
};

//concrete handlers
class Handler1: public Handler//handles if value<=limit
{
private:
	int limit;
	int ID;
public:
	Handler1(int _l, int _i) :limit(_l), ID(_i) {}

	void handleRequest(int value)
	{
		if (value <= limit)
		{
			cout << "handler1, with id = " << this->ID << " handled request with limit: " << this->limit << endl;
			//nextHandler->handleRequest(value);//if we want that all handlers can handle it
		}
		else if(this->nextHandler !=NULL)
		{
			nextHandler->handleRequest(value);
		}
		else//last in clain, so unhandled
		{
			cout << "event was unhandled" << endl;
		}
	}
};

class Handler2 : public Handler//handles if value==number
{
private:
	int number;
	int ID;
public:
	Handler2(int _n, int _i) :number(_n), ID(_i) {}

	void handleRequest(int value)
	{
		if (value == number)
		{
			cout << "handler2, with id = " << this->ID << " handled request with number: " << this->number << endl;
			//nextHandler->handleRequest(value);// add bool variable here(if was handled)
		}
		else if (this->nextHandler != NULL)
		{
			nextHandler->handleRequest(value);
		}
		else//last in clain, so unhandled
		{
			cout << "event was unhandled" << endl;
		}
	}
};

int main()
{
	Handler* h1_1 = new Handler1(10, 1);
	Handler* h1_2 = new Handler1(20, 2);
	Handler* h2_1 = new Handler2(17, 3);
	Handler* h2_2 = new Handler2(25, 4);

	h1_1->setNextHandler(h1_2);
	h1_2->setNextHandler(h2_1);
	h2_1->setNextHandler(h2_2);
	
	h1_1->handleRequest(17);

	system("PAUSE");
	return 0;
}




















