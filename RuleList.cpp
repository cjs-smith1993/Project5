#include "RuleList.h"

using namespace std;

RuleList::RuleList()
{
	rlc=0;
}

void RuleList::add_rule(Rule* s)
{
	rvec.push_back(s);
	rlc++;
}

string RuleList::print()
{
	stringstream ss;
	ss<<"Rules"<<"("<<rlc<<")"<<":\n";
	for(int i=0; i<rvec.size();i++)
	{
		ss<<rvec.at(i)->print();
	}
	
	return ss.str();
}

RuleList::~RuleList()
{
}