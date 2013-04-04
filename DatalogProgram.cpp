#include "DatalogProgram.h"
#include "TokenType.h"

#include <vector>

using namespace std;
DatalogProgram::DatalogProgram(vector<Token*>* t) 
{
	tokens=new vector<Token*>();
  for(int o=0;o<t->size();o++)
    {
	  if(t->at(o)->getTokenType()!=COMMENT)
	  {
		  tokens->push_back(t->at(o));
	  }
	}
	success=true;
	index=0;
}

void DatalogProgram::advance()
{
  index++;
}

void DatalogProgram::parse()
{
  if(tokens->at(index)->getTokenType() == SCHEMES)
	{
	  advance();
	  if(tokens->at(index)->getTokenType()  == COLON)
	  {
		sl=new SchemeList();
	    advance();
        pschemeList();
	  }
	  else
	  {
		  success=false;
		  return;
	  }
	}
  
  if(tokens->at(index)->getTokenType() == FACTS && success==true)
	{
	  advance();
	  if(tokens->at(index)->getTokenType() == COLON)
	    {
		  d=new Domain();
		  fl=new FactList();
	      advance();
	      pfactList();
	    }
	  else
	  {
		  success=false;
		  return;
	  }
	}
  else
  {
	  success=false;
  }
  
  if(tokens->at(index)->getTokenType() == RULES && success==true)
	{
		advance();
		if(tokens->at(index)->getTokenType() == COLON)
		{
			rl=new RuleList();
			advance();
			pruleList();
		}
		else
		{
			success=false;
			return;
		}
	}
  else
  {
	  success=false;
  }
  if(tokens->at(index)->getTokenType() == QUERIES && success==true)
	{
		advance();
		if(tokens->at(index)->getTokenType() == COLON)
		{
			ql=new QueryList();
			advance();
			pqueryList();
		}
		else
		{
			success=false;
			return;
		}
		
	}
  
  else
  {
	  success=false;
  }
    /*
    if(success==true)
    {
        cout<<"Success!"<<endl;
        cout<<print();
        //cout the the toStrings all together;
    }
    else
    {
        cout<<"Failure!"<<endl;
        string k=failure();
        cout<<k<<endl;
        //cout the failing line;
    }
    */
    
    
  return;
}

void DatalogProgram::pqueryList()
{
		if(tokens->at(index)->getTokenType()!=ID)
		{
			success=false;
			return;
		}
		
		else
		{
			pquery();
			if(tokens->at(index)->getTokenType()==END_OF_FILE)
			{
				return;
			}
			if(success==true)
			{
				advance();
			}
			else
			{
				return;
			}
			if(tokens->at(index)->getTokenType()==ID)
			{
				pqueryList();
			}
			else
			{
				return;
			}
		}
}

void DatalogProgram::pquery()
{
	Query* query= new Query();
	ql->add_que(query);
	pqpredicateList();
	return;
}

void DatalogProgram::pruleList()
{
	
	if(tokens->at(index)->getTokenType()==ID)
	{
		prule();
		if(success==false)
		{
			return;
		}
		advance();
		if(tokens->at(index)->getTokenType()==QUERIES)
		{
			return;
		}
		else if(tokens->at(index)->getTokenType()==COMMA || tokens->at(index)->getTokenType()==ID)
		{
			pruleList();
		}
		else
		{ 
			success=false;
			return;
		}
	}
	
	else
	{
		return;
	}
}

void DatalogProgram::prule()
{
	rule= new Rule();
	rl->add_rule(rule);
	if(tokens->at(index)->getTokenType() != ID)
    {
      success=false;
      return;
    }
  else
    {
	  rule->first=(tokens->at(index));
      advance();
    }
  if(tokens->at(index)->getTokenType() != LEFT_PAREN)
    {
      success =false;
      return;
    }
  else
    {
      advance();
	  while(!ids.empty())
	  {
		  ids.pop_back();
	  }
      pidentifierList();
	  for(int i=0; i<ids.size();i++)
	  {
		  rule->add_id(ids.at(i));
	  }

    }
	if(tokens->at(index)->getTokenType()!=COLON_DASH)
	{
		success=false;
		return;
	}
	else
	{
		advance();
		ppredicateList();
	}
	return;
}

void DatalogProgram::ppredicateList()
{
	p=new Predicate();
	rule->j.push_back(p);
	ppredicate();
	advance();
	if(tokens->at(index)->getTokenType()!=COMMA)
	{
		if(tokens->at(index)->getTokenType()!=RIGHT_PAREN)
		{
			if(tokens->at(index)->getTokenType()!=PERIOD)
			{
				success=false;
				return;
			}
			else
			{
				return;
			}
			
		}
	}
	else
	{
		advance();
		ppredicateList();
	}
}

void DatalogProgram::ppredicate()
{
	
	if(tokens->at(index)->getTokenType()!=ID)
	{
		success=false;
		return;
	}
	else
	{
		p->first=tokens->at(index);
		advance();
		if(tokens->at(index)->getTokenType()!=LEFT_PAREN)
		{
			success=false;
			return;
		}
		else
		{
			advance();
			pparameterList();
		}
	}
	return;
}

void DatalogProgram::pparameterList()
{
	par=new Parameter();
	p->add_parameter(par);
	pparameter();
	if(tokens->at(index)->getTokenType()!=COMMA)
	{
		if(tokens->at(index)->getTokenType()!=RIGHT_PAREN)
		{
			success=false;
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		advance();
		pparameterList();
	}
}

void DatalogProgram::pparameter()
{

	if(tokens->at(index)->getTokenType()==STRING || tokens->at(index)->getTokenType()==ID)
	{
		par->add_content(tokens->at(index));
		if(tokens->at(index)->getTokenType()==STRING)
		{
			d->add_domain(tokens->at(index)->getTokensValue());
		}
		advance();
	}
	else if(tokens->at(index)->getTokenType()==LEFT_PAREN)
	{
		par->add_content(tokens->at(index));
		advance();
		pexpression();
		if(tokens->at(index)->getTokenType()==RIGHT_PAREN)
		{
			par->add_content(tokens->at(index));
			advance();
		}
		else
		{
			success=false;
		}
	}
	else
	{
		success=false;
		return;
	}
	
}

void DatalogProgram::pexpression()
{
	pparameter();
	if(tokens->at(index)->getTokenType()==MULTIPLY|| tokens->at(index)->getTokenType()==ADD)
	{
		par->add_content(tokens->at(index));
		advance();
	}
	else
	{
		success=false;
	}
	pparameter();
}

void DatalogProgram::pqpredicateList()
{
	q=new Predicate();
	ql->j.push_back(q);
	pqpredicate();
	advance();
	if(tokens->at(index)->getTokenType()!=COMMA)
	{
		if(tokens->at(index)->getTokenType()!=RIGHT_PAREN)
		{
			if(tokens->at(index)->getTokenType()!=Q_MARK)
			{
				success=false;
				return;
			}
			else
			{
				return;
			}
		}
	}
	else
	{
		advance();
		pqpredicateList();
	}
}

void DatalogProgram::pqpredicate()
{
	
	if(tokens->at(index)->getTokenType()!=ID)
	{
		success=false;
		return;
	}
	else
	{
		q->first=tokens->at(index);
		advance();
		if(tokens->at(index)->getTokenType()!=LEFT_PAREN)
		{
			success=false;
			return;
		}
		else
		{
			advance();
			pqparameterList();
		}
	}
}
void DatalogProgram::pqparameterList()
{
	par=new Parameter();
	q->add_parameter(par);
	pqparameter();
	if(tokens->at(index)->getTokenType()!=COMMA)
	{
		if(tokens->at(index)->getTokenType()!=RIGHT_PAREN)
		{
			success=false;
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		advance();
		pqparameterList();
	}
}

void DatalogProgram::pqparameter()
{
	if(tokens->at(index)->getTokenType()==STRING || tokens->at(index)->getTokenType()==ID)
	{
		par->add_content(tokens->at(index));
		if(tokens->at(index)->getTokenType()==STRING)
		{
			d->add_domain(tokens->at(index)->getTokensValue());
		}
		advance();
	}
	else if(tokens->at(index)->getTokenType()==LEFT_PAREN)
	{
		par->add_content(tokens->at(index));
		advance();
		pqexpression();
		if(tokens->at(index)->getTokenType()==RIGHT_PAREN)
		{
			par->add_content(tokens->at(index));
			advance();
		}
		else
		{
			success=false;
		}
	}
	else
	{
		success=false;
		return;
	}
	
}

void DatalogProgram::pqexpression()
{
	pqparameter();
	if(tokens->at(index)->getTokenType()==MULTIPLY|| tokens->at(index)->getTokenType()==ADD)
	{
		par->add_content(tokens->at(index));
		advance();
	}
	else
	{
		success=false;
	}
	pqparameter();
}

void DatalogProgram::pfactList()
{

	pfact();
	if(tokens->at(index)->getTokenType()==ID)
	{
		pfactList();
	}
	return;
}

void DatalogProgram::pfact()
{
	
	if(tokens->at(index)->getTokenType()!=ID)
	{
		return;
	}
	else
	{
		Fact* fact = new Fact();
		fl->add_fact(fact);
		fact->first=tokens->at(index);
		advance();
		if(tokens->at(index)->getTokenType()!=LEFT_PAREN)
		{
			success=false;
			return;
		}
		else
		{
			advance();
			while(!cl.empty())
			{
				cl.pop_back();
			}
			pconstantList();
			for(int i=0; i<cl.size();i++)
			{
				fact->add_fact(cl.at(i));
				d->add_domain(cl.at(i));
			}
		}
		
	}
}

void DatalogProgram::pconstantList()
{
	if(tokens->at(index)->getTokenType()!=STRING)
	{
		success=false;
		return;
	}
	else
	{
		cl.push_back(tokens->at(index)->getTokensValue());
		advance();
		if(tokens->at(index)->getTokenType() != COMMA)
		{
		   if(tokens->at(index)->getTokenType() !=RIGHT_PAREN)
		   {
			  success=false;
			  return;
		   }
		   else
		   {
			  advance();
			  if(tokens->at(index)->getTokenType() != PERIOD)
			  {
				  success=false;
				  return;
			  }
			  else
			  {
				  advance();
				  return;
			  }
		   }
		}
	   else
	   {
		   advance();
		   pconstantList();
	   }
	}
}

void DatalogProgram::pschemeList()
{
  pscheme();
  if(tokens->at(index)->getTokenType()==ID)
    {
      pschemeList();
    }
  return;
}

void DatalogProgram::pscheme()
{ 
	Scheme * sch = new Scheme();
	sl->add_scheme(sch);
  if(tokens->at(index)->getTokenType() != ID)
    {
      success=false;
      return;
    }
  else
    {
		
	  sch->first=(tokens->at(index));
      advance();
    }
  if(tokens->at(index)->getTokenType() != LEFT_PAREN)
    {
      success =false;
      return;
    }
  else
    {
      advance();
	  while(!ids.empty())
	  {
		  ids.pop_back();
	  }
      pidentifierList();
	  for(int i=0; i<ids.size();i++)
	  {
		  sch->add_id(ids.at(i));
	  }

    }
  return;
}
void DatalogProgram::pidentifierList()
{
  if(tokens->at(index)->getTokenType()!= ID)
    {
      success=false;
      return;
    }
  else
    {
	  ids.push_back(tokens->at(index));
      advance();
      if(tokens->at(index)->getTokenType() != COMMA)
         {
           if(tokens->at(index)->getTokenType() !=RIGHT_PAREN)
           {
         	  success=false;
         	  return;
           }
           else
           {
         	  advance();
			  return;
           }
         }
       else
         {
           advance();
           pidentifierList();
         }
    }
}

string DatalogProgram::failure()
{
	return tokens->at(index)->toString();
}

string DatalogProgram::print()
{
	string stuff;
	stringstream ss;
	ss<<sl->print();
	ss<<fl->print();
	ss<<rl->print();
	ss<<ql->print();
	ss<<d->print();
	return ss.str();
}

DatalogProgram::~DatalogProgram()
{
}
