#include "Fact.h"

using namespace std;

Fact::Fact()
{
}

void Fact::add_fact(string j)
{
	cl.push_back(j);
}

string Fact::print()
{
	stringstream ss;
	for(int i=0; i<cl.size(); i++)
	{
		ss<<cl.at(i);
		int j=(int)(cl.size()-i);
		if(j!=1)
		{
			ss<<",";
		}
	}
	return ss.str();
}

Fact::~Fact()
{
}
