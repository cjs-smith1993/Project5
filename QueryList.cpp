#include "QueryList.h"

using namespace std;

QueryList::QueryList()
{
	qlc=0;
}

void QueryList::add_que(Query* t)
{
	qvec.push_back(t);
	qlc++;
}

string QueryList::print()
{
	stringstream ss;
	ss<<"Queries("<<qlc<<"):\n";
	for(int i=0; i<j.size();i++)
	{
		ss<<"  "<<j.at(i)->print();
		int k=(int)(j.size()-i);
		if(k!=1)
		{
			ss<<",";
		}
	}
	ss<<"?\n";
	return ss.str();
}

QueryList::~QueryList()
{
}