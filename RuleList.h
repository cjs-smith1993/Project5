#ifndef Rule_List_h
#define Rule_List_h

#include <string>
#include <vector>
#include "Rule.h"



using namespace std;

//uses this part of the grammar
//<Rule> <Rule List> | E
class RuleList
{
public:
	RuleList();
	~RuleList();
	vector<Rule*>rvec;
	void add_rule(Rule*);
	vector<Predicate*> j;
	string print();
	int rlc;

private:
};

#endif