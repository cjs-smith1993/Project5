#include "Domain.h"

using namespace std;

Domain::Domain()
{
	count=0;
}

void Domain::add_domain(string j)
{
	bool exists=true;	
	for(int i=0; i<dl.size(); i++)
	{
		if(dl.at(i)==j)
		{
			exists=false;
		}
	}
	if(exists==true)
	{
		dl.push_back(j);
		count++;
	}
	return;
}

void Domain::sort()
{
	for(int i=0; i<dl.size();i++)
	{
		mylist.push_back(dl.at(i));
	}
	mylist.sort();
}

string Domain::print()
{
	sort();
	stringstream ss;
	ss<<"Domain"<<"("<<count<<"):"<<endl;
	int count=0;
	for (list<string>::iterator it=mylist.begin(); it != mylist.end(); ++it)
	{
		
		ss<<"  "<<*it;
		int j=(int)(dl.size()-count);
		if(j!=1)
		{
			ss<<"\n";
		}
		count++;
	}
	ss<<endl;
	return ss.str();
}

Domain::~Domain()
{
}