#include<iostream>
#include<string>
using namespace std;

//Strategy
class Compression
{
public:
	virtual ~Compression() {}
	virtual void compress(const string& file) = 0;
};

//concrete strategies
class ZIPCompression:public Compression
{
public:
	void compress(const string& file)
	{
		cout << "ZIP compressed" << endl;
	}
};

class RARCompression : public Compression
{
public:
	void compress(const string& file)
	{
		cout << "RAR compressed" << endl;
	}
};

//Context
class Compressor
{
private:
	Compression* comp;//they also use &
public:
	Compressor(Compression* _comp) : comp(_comp) {}
	~Compressor() { delete comp; }

	void compress(const string& file)//execute
	{
		comp->compress(file);
	}
};

int main()
{
	Compressor* c = new Compressor(new ZIPCompression);

	c->compress("file");
	delete c;
	system("PAUSE");
	return 0;
}