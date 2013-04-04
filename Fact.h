#ifndef Fact_h
#define Fact_h

#include <string>
#include <vector>
#include <sstream>
#include "TokenType.h"
#include "Lex.h"
#include <iostream>

using namespace std;

class Fact
{
public:
	Fact();
	~Fact();
	vector<string>cl;
	Token* first;
	void add_fact(string j);
	string print();

private:

};

#endif