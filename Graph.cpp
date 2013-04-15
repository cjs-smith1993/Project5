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
        
        int pos = -1;
        for (int j = 0; j < adjList.size(); j++) { //Loop through the rule heads
            if (headName.compare(adjList.at(j).front()) == 0) {
                pos = j; //Store the position of the rule that is in the adjacency list
            }
        }
        
        for (int j = 0; j < rules.at(i)->j.size(); j++) { //Loop through the predicates of each rule
            std::string predName = rules.at(i)->j.at(j)->first->getTokensValue(); //Get the name of the predicate
            
            if (heads.count(predName) != 0) { //If the predicate is a head in another rule
                
                bool added = false;
                for (int k = 1; k < adjList.at(pos).size() - 1; k++) { //Loop through the predicates that the head depends on
                    if (predName.compare(adjList.at(pos).at(k)) == 0) { //If the predicate has already been added
                        added = true;
                    }
                }
                if (!added) { //If the predicate has not already been added
                    adjList.at(pos).push_back(predName); //Add the predicate to the adjacency list
                }
            }
        }
    }
    
    //print();
}

Graph::~Graph() {
    
}

void Graph::genPONums(std::string queryName){
    /*
  std::stack<string> DFTstack;
  std::map<std::string, bool> visited;
  int line=0;
  
  //problems
  //while adding things to the visited how to associate predicates with head predicates
  //from there should be able to go through and push and pop on the stack accordingly
  for(int i = 0; i < adjList.size(); i++)//add all predicates to the visited map; go through lists
  {
    for(int j = 0; j < adjList.at(i).size(); j++)// go through content of each list to add to visited
    {
      //go through the interator of at(i);
      node* temp=adjList.at(i).begin().//value???;
      visited.insert (temp, false);
      temp=temp.next();
      
    }
  }
  
  //start at queryName;
  for(int i = 0; i < visited.size(); i++)
  {
      if(visited.at(i)==false)
      {
         DFTstack.push_back(map.at(i)->first);
         visited.at(i)=true;
      }
      else
      {
          
      }
  }
     */
}

bool Graph::detectCycles() {
    bool cycles = false;
    
    for (int i = 0; i < adjList.size(); i++) { //Loop through all of the rules
        for (int j = 1; j < adjList.at(i).size(); j++) { //Loop through all of the rules the current head depends on
            if (postNums[adjList.at(i).at(0)] <= postNums[adjList.at(i).at(j)]) { //If there is a backward edge
                cycles = true;
            }
        }
    }
    
    std::cout << cycles << endl;
    return cycles;
}

void Graph::print() {
    for (int i = 0; i < adjList.size(); i++) {
        for (int j = 0; j < adjList.at(i).size(); j++) {
            std::cout << adjList.at(i).at(j);
            if (j == 0)
                std::cout << ": ";
            else if (j < adjList.at(i).size() - 1)
                std::cout << ", ";
        }
        std::cout << endl;
    }
}
