#include "SchemeList.h"

using namespace std;

SchemeList::SchemeList()
{
	slc=0;
}

void SchemeList::add_scheme(Scheme* s)
{
	svec.push_back(s);
	slc++;
}

string SchemeList::print()
{
	stringstream ss;
	ss<<"Schemes"<<"("<<slc<<")"<<":\n";
	for(int i=0; i<svec.size();i++)
	{
		ss<<"  "<<svec.at(i)->first->getTokensValue()<<"(";
		ss<<svec.at(i)->print();
		ss<<")\n";
	}
	return ss.str();
}

SchemeList::~SchemeList()
{
}