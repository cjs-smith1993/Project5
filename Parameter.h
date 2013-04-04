#ifndef Parameter_h
#define Parameter_h

#include <string>
#include <vector>
#include <sstream>
#include "TokenType.h"
#include "Lex.h"

using namespace std;

//this part of the grammar contains
// <String> | <Identifier> | <Expression> 
class Parameter
{
public:
	Parameter();
	~Parameter();
	vector<Token*> content;
	void add_content(Token * j);
	string print();

private:
};
#endif