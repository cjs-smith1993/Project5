#ifndef Scheme_List_h
#define Scheme_List_h

#include <string>
#include <sstream>
#include <iostream>
#include "Lex.h"
#include "Scheme.h"
using namespace std;

// uses this part of the grammar
// <Scheme> <Scheme List Tail>
class SchemeList
{
public:
	SchemeList();
	~SchemeList();
	vector<Scheme*> svec;
	string print();
	void add_scheme(Scheme*);
	int slc;
	


private:
};

#endif