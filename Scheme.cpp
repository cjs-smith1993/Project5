#include "Scheme.h"

using namespace std;

Scheme::Scheme()
{
}

void Scheme::add_id(Token* i)
{
	idl.push_back(i);
}

string Scheme::print()
{
	stringstream ss;
	for(int i=0; i<idl.size(); i++)
	{
		ss<<idl.at(i)->getTokensValue();
		int j=(int)(idl.size()-i);
		if(j!=1)
		{
			ss<<",";
		}
	}
	return ss.str();
}

Scheme::~Scheme()
{
}


