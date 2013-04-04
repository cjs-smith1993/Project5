#include "FactList.h"

using namespace std;

FactList::FactList()
{
	flc=0;
}

void FactList::add_fact(Fact * f)
{
	fvec.push_back(f);
	flc++;
}

string FactList::print()
{
	stringstream ss;
	ss<<"Facts"<<"("<<flc<<")"<<":\n";
	if(fvec.size()!=0)
	{
		for(int i=0; i<fvec.size();i++)
		{
			ss<<"  "<<fvec.at(i)->first->getTokensValue()<<"(";
			ss<<fvec.at(i)->print();
			ss<<").\n";
		}
	}
	return ss.str();
}

FactList::~FactList()
{
}