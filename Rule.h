#ifndef Rule_h
#define Rule_h

#include <string>
#include <sstream>
#include <iostream>
#include "Lex.h"
#include "TokenType.h"
#include "Predicate.h"


using namespace std;

//uses this part of the grammar
// <Head Predicate> :- <Predicate List> . 
class Rule
{
public:
	Rule();
	~Rule();
	vector<Token*>hpl;
	void add_id(Token*);
	vector<Predicate*> j;
	Token* first;
	string print();

private:
};

#endif