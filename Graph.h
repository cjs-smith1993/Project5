//
//  Graph.h
//  Project5
//
//  Created by Connor Smith on 4/13/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#ifndef __Project5__Graph__
#define __Project5__Graph__

#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <map>

#include "Rule.h"

class Graph {
    
public:
    std::vector<std::list<std::string> > adjList;
    std::map<std::string, int> postNums;
    
    Graph();
    Graph(std::vector<Rule*> rules);
    ~Graph();
    void createAdjList();
    void traverse();
    bool detectCycles();

};

#endif /* defined(__Project5__Graph__) */
