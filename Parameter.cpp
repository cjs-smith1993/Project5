#include "Parameter.h"

using namespace std;

Parameter::Parameter()
{
}

void Parameter::add_content(Token* j)
{
	content.push_back(j);
}

string Parameter::print()
{
	stringstream ss;
	for(int i=0; i<content.size(); i++)
	{
		ss<<content.at(i)->getTokensValue();
	}
	return ss.str();
}

Parameter::~Parameter()
{
}