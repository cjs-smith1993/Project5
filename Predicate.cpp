#include "Predicate.h"

using namespace std;

Predicate::Predicate()
{
}

void Predicate::add_parameter(Parameter* j)
{
	parl.push_back(j);
}

string Predicate::print()
{
	stringstream ss;
	ss<<first->getTokensValue()<<"(";
	for(int i=0; i<parl.size();i++)
	{
		ss<<parl.at(i)->print();
		int j=(int)(parl.size()-i);
		if(j!=1)
		{
			ss<<",";
		}
	}
	ss<<")";
	return ss.str();
}

Predicate::~Predicate()
{
}