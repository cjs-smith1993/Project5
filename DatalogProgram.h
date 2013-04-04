#ifndef Datalog_Program_h
#define Datalog_Program_h

#include<string>
#include <iostream>
#include <sstream>
#include "SchemeList.h"
#include "FactList.h"
#include "RuleList.h"
#include "QueryList.h"
#include "Domain.h"
#include "Lex.h"
#include <vector>

using namespace std;

//chooses schemes facts rules or queries or <EOF>
class DatalogProgram
{
public:
	DatalogProgram(vector<Token*>* t);
	~DatalogProgram();
	void parse();
	void pscheme();
	void pschemeList();
	void pfact();
	void pfactList();
	void prule();
	void pruleList();
	void domain();
	void pqueryList();
	void pquery();
	void pparameter();
	void pexpression();
	void pparameterList();
	void ppredicate();
	void ppredicateList();
	void pqparameter();
	void pqexpression();
	void pqparameterList();
	void pqpredicate();
	void pqpredicateList();
	void pidentifierList();
	void pconstantList();
	string print();
	vector<Token*>* tokens;
	vector<Token*> ids;
	vector<string> cl;
	vector<Parameter*> prel;
	vector<Token*> parl;
	string failure();
	Lex * lex;
	int index;
	SchemeList * sl;
	FactList * fl;
	RuleList * rl;
	Rule* rule;
	QueryList * ql;
	Domain * d;
	Predicate* p;
	Predicate* q;
	Parameter* par;
	Token* getCurrentToken();
	void advance();
	bool success;
private:
};

#endif