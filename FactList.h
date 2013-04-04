#ifndef Fact_List_h
#define Fact_List_h

#include <string>
#include "Fact.h"
#include <vector>

using namespace std;

//this part of the grammar uses
//<Fact List>  -> <Fact> <Fact List> | E
class FactList
{
public:
	FactList();
	~FactList();
	vector<Fact*> fvec;
	void add_fact(Fact *);
	string print();
	int flc;

private:
};

#endif