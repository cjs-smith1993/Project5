//
//  Relation.h
//  Project3
//
//  Created by Connor Smith on 3/14/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#ifndef __Project3__Relation__
#define __Project3__Relation__

#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

#include "Tuple.h"
#include "Schema.h"
#include "Fact.h"
#include "Parameter.h"
#include "Pair.h"

class Relation {
public:
    std::string name;
    Schema* columns;
    std::vector<Tuple*> facts;
    
    Relation();
    Relation(Token* n, std::vector<Token*> schema);
    ~Relation();
    
    void addTuple(Fact* f);
    static bool tupleCompare(Tuple* t1, Tuple* t2);
    Relation* processQuery(std::vector<Parameter*> a);

    Relation* rename(string oldAttr, string newAttr);
    Relation* project(std::vector<std::string> columns);
    Relation* selectConstant(Pair* p);
    Relation* selectVariables(std::vector<int> vars);
    
    Relation* copy();
    std::string print(std::vector<Parameter*> args);
};

#endif /* defined(__Project3__Relation__) */
