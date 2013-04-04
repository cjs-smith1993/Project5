#ifndef Scheme_h
#define Scheme_h

#include <string>
#include <sstream>
#include <iostream>
#include "Lex.h"
#include "TokenType.h"

using namespace std;

//uses this part of the grammar
// <Identifier> ( <Identifier List> )
class Scheme
{
public:
	Scheme();
	~Scheme();
	vector<Token*>idl;
	void add_id(Token*);
	string print();
	Token* first; 
	


private:
};

#endif