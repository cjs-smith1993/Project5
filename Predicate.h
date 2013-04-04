#ifndef Predicate_h
#define Predicate_h

#include <string>
#include <vector>
#include <sstream>
#include "TokenType.h"
#include "Parameter.h"

using namespace std;

//this contains this part of the grammar
// <Identifier> ( <Parameter List> )
class Predicate
{
public:
	Predicate();
	~Predicate();
	Token* first;
	vector<Parameter*>parl;
	void add_parameter(Parameter* j);
	string print();
private:
};
#endif