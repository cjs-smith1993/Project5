#include "Rule.h"

using namespace std;

Rule::Rule()
{
}

void Rule::add_id(Token* i)
{
	hpl.push_back(i);
}

string Rule::print()
{
	stringstream ss;
	ss<<"  "<<first->getTokensValue()<<"(";
	for(int i=0; i<hpl.size(); i++)
	{
		ss<<hpl.at(i)->getTokensValue();
		int j=(int)(hpl.size()-i);
		if(j!=1)
		{
			ss<<",";
		}
	}
	ss<<")"<<" :- ";
	for(int c=0; c<j.size();c++)
		{
			ss<<j.at(c)->print();
			//int k=(j.size()-c);
		}
		ss<<".\n";
	return ss.str();
}

Rule::~Rule()
{
}