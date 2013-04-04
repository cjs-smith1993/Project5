#ifndef Domain_h
#define Domain_h

#include <string>
#include <vector>
#include <sstream>
#include <list>
#include "TokenType.h"
#include "Lex.h"
#include <iostream>

using namespace std;

class Domain
{
public:
	Domain();
	~Domain();
	vector<string>dl;
	void add_domain(string j);
	string print();
	int count;
	list<string>mylist;
	void sort();
	
private:
};

#endif