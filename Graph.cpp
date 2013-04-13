//
//  Graph.cpp
//  Project5
//
//  Created by Connor Smith on 4/13/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#include "Graph.h"

Graph::Graph() {
    
}

Graph::Graph(std::vector<Rule*> rules) {
    adjList.clear();
    
    std::set<std::string> heads; //Set to keep track of rule heads that have already been added
    
    for (int i = 0; i < rules.size(); i++) { //Loop through the rules
        std::vector<std::string> list;
        std::string headName = rules.at(i)->first->getTokensValue(); //Get the name of the rule
        
        if (heads.count(headName) == 0) { //If the rule hasn't already been added
            heads.insert(headName); //Mark that it has been added
            list.push_back(headName);
            adjList.push_back(list); //Add the rule as a head in the adjacency list
        }
    }
    
    for (int i = 0; i < rules.size(); i++) { //Loop through the rules again
        std::string headName = rules.at(i)->first->getTokensValue(); //Get the name of the rule
                
        for (int j = 0; j < rules.at(i)->j.size(); j++) { //Loop through the predicates of each rule
            std::string predName = rules.at(i)->j.at(j)->first->getTokensValue(); //Get the name of the predicate
            
            if (heads.count(predName) != 0) { //If the predicate is a head in another rule
                
                for (int k = 0; k < adjList.size(); k++) { //Loop through the rule heads
                    if (headName.compare(adjList.at(k).front()) == 0) { //Find the head matching the rule name
                        
                        bool added = false;
                        for (int l = 1; l < adjList.at(k).size() - 1; l++) { //Loop through the predicates that the head depends on
                            if (predName.compare(adjList.at(k).at(l)) == 0) { //If the predicate has already been added
                                added = true;
                            }
                        }
                        if (!added) { //If the predicate has not already been added
                            adjList.at(k).push_back(predName); //Add the predicate to the adjacency list
                        }
                    }
                }
            }
        }
    }
}

Graph::~Graph() {
    
}

void Graph::genPONums(std::string queryName){
  std::stack<string> DFTstack;
}

bool Graph::detectCycles() {
    return true;
}