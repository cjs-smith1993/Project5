//
//  Database.h
//  Project3
//
//  Created by Connor Smith on 3/14/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#ifndef __Project3__Database__
#define __Project3__Database__

#include <iostream>
#include <vector>

#include "Relation.h"
#include "Rule.h"
#include "DatalogProgram.h"
#include "Graph.h"

class Database {
public:
    std::vector<Relation*> relations;
    std::vector<Rule*> rules;
    std::vector<std::string> domain;
    DatalogProgram* parser;
    
    Database(DatalogProgram* parser);
    ~Database();
    void addRelation(Relation* r);
    void addTuples();
    void addRules();
    void processQueries();
    void processRules(std::string queryName);
    void processRule(Rule* r);
    
    Relation* join(std::vector<Relation*> relationList);
    Relation* cross(Relation* r1, Relation* r2);
    Relation* getHeadRelation(Rule* rule);
    std::vector<Relation*> getRelationList(std::vector<Predicate*> predicateList);
    std::vector<std::string> getHeadVariables(std::vector<Token*> headParameterList);
    Relation* renameToMatch(Relation* headRelation, Relation* newRelation, std::vector<std::string> headVariables);
    Relation* unionWith(Relation* r1, Relation* r2);
    int getNumFacts();
};

#endif /* defined(__Project3__Database__) */
