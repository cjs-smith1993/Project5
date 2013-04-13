//
//  Database.cpp
//  Project3
//
//  Created by Connor Smith on 3/14/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#include "Database.h"

Database::Database(DatalogProgram* p) {
    parser = p;

    std::vector<Scheme*> svec = parser->sl->svec;
    for (int i = 0; i < svec.size(); i++) { //Loop through the list of schemes
        Token* name = svec.at(i)->first;
        std::vector<Token*> schema = svec.at(i)->idl;
        Relation* r = new Relation(name, schema); //Create a new relation with the name and attributes of each scheme
        addRelation(r); //Add the relation to the database
    }
    
    addTuples(); //Populate the database
    addRules(); //Add the rules to the database
    g = new Graph(rules); //Generate a depends-on graph for the rules
    //processRules(); //Generate new facts
}

Database::~Database() {
    for (int i = 0; i < relations.size(); i++)
        delete relations.at(i);
}

void Database::addRelation(Relation* r) {
    relations.push_back(r);
}

void Database::addTuples() {
    std::vector<Fact*> fvec = parser->fl->fvec;
    for (int i = 0; i < fvec.size(); i++) { //Loop through the list of facts
        std::string name = fvec.at(i)->first->getTokensValue(); //Get the name of the schema
        
        for (int j = 0; j < relations.size(); j++) { //Loop through the list of relations
            if (name.compare(relations.at(j)->name) == 0) { //If the fact's schema matches a relation
                relations.at(j)->addTuple(fvec.at(i)); //Add the fact to the relation
            }
        }
    }
}

void Database::addRules() {
    std::vector<Rule*> rvec = parser->rl->rvec;
    for (int i = 0; i < rvec.size(); i++) { //Loop through the list of rules
        rules.push_back(rvec.at(i)); //Add the rule to the database
    }
}

void Database::processQueries () {
    std::vector<Predicate*> pred = parser->ql->j;
    for (int i = 0; i < pred.size(); i++) { //Loop through the list of queries
        std::string name = pred.at(i)->first->getTokensValue(); //Get the name of the schema
        
        for (int j = 0; j < relations.size(); j++) { //Loop through the list of relations
            if (name.compare(relations.at(j)->name) == 0) { //If the query's schema matches a relation
                processRules(name);
                Relation* r = relations.at(j)->processQuery(pred.at(i)->parl); //Process the query with that relation
                std::cout << r->print(pred.at(i)->parl);
            }
        }
    }
    
    //std::cout << "Done!";
}

void Database::processRules(std::string queryName) {
    g->genPONums(queryName); //Generate the post-order numbers for the query
    
    if (g->detectCycles()) {
        int numFacts = 0;
        int passes = 0;
        do {
            passes++;
            numFacts = getNumFacts(); //Get the current number of facts
            for (int i = 0; i < rules.size(); i++) { //Loop through the rules
                processRule(rules.at(i)); //Generate new facts
            }
        } while (numFacts != getNumFacts()); //Repeat until no new facts have been generated

        //std::cout << "Schemes populated after " << passes << " passes through the Rules.\n";
    }
    
    else {
        for (int i = 0; i < rules.size(); i++) { //Loop through the rules once
            processRule(rules.at(i)); //Generate new facts
        }
    }
}

void Database::processRule(Rule* rule) {
    //Find the relation in the list of schemes matching the head of the predicate
    Relation* headRelation = getHeadRelation(rule);
    
    //Get the list of predicates
    std::vector<Predicate*> predicateList = rule->j;
    
    //Create new relations from each predicate
    std::vector<Relation*> relationList = getRelationList(predicateList);
    
    //Natural join the relations from the predicates
    Relation* newRelation = join(relationList);
    
    //Project on the final relation; only keep columns matching variables in the rule head
    std::vector<std::string> headVariables = getHeadVariables(rule->hpl);
    newRelation = newRelation->project(headVariables);
    
    //Find the relation in the database that matches the head of the rule
        //Already done (it's headRelation)
    
    //Rename attributes in the new relation so it matches the rule head's schema
    newRelation = renameToMatch(headRelation, newRelation, headVariables);
    
    //Union the new relation with the matching relation
    headRelation = unionWith(headRelation, newRelation);
    std::sort(headRelation->facts.begin(), headRelation->facts.end(), Relation::tupleCompare);
}

Relation* Database::join(std::vector<Relation*> relationList) {
    Relation* newRelation = relationList.at(0)->copy(); //Start with the first relation in the list
    if (newRelation == NULL) //If the list is empty, do nothing
        return NULL;
    
    for (int i = 1; i < relationList.size(); i++) { //Loop through the list of relations
        newRelation = cross(newRelation, relationList.at(i)); //Join the relations one at a time
        
        //Handle duplicate columns
        for (int j = 0; j < newRelation->columns->attributes.size(); j++) { //Loop through the attributes of the relation
            std::string a1 = newRelation->columns->attributes.at(j);
            for (int k = j+1; k < newRelation->columns->attributes.size(); k++) { //Loop through the attributes of the relation
                std::string a2 = newRelation->columns->attributes.at(k);
                if (a1.compare(a2) == 0) { //If there are duplicates
                    std::vector<int> vars;
                    vars.push_back(j);
                    vars.push_back(k);
                    newRelation = newRelation->selectVariables(vars); //Select on duplicate columns
                    
                    newRelation = newRelation->rename(a1, a1 + "'"); //Rename duplicate
                    
                    std::vector<std::string> columns;
                    for (int l = 0; l < newRelation->columns->attributes.size(); l++) { //Loop through columns to project on
                        if (l != k) {
                            columns.push_back(newRelation->columns->attributes.at(l));
                        }
                    }
                    newRelation = newRelation->project(columns); //Project out the duplicate column
                    
                    newRelation = newRelation->rename(a1 + "'", a1); //Rename B' back to B
                }
            }
        }
    }
    
    return newRelation;
}

Relation* Database::cross(Relation* r1, Relation* r2) {
    Relation* newRelation = new Relation(); //Start with the first relation
    
    //Combine the attribute lists
    for (int i = 0; i < r1->columns->attributes.size(); i++) {
        newRelation->columns->attributes.push_back(r1->columns->attributes.at(i));
    }
    for (int i = 0; i < r2->columns->attributes.size(); i++) {
        newRelation->columns->attributes.push_back(r2->columns->attributes.at(i));
    }
    
    //Combine the fact lists
    for (int i = 0; i < r1->facts.size(); i++) { //Loop through the facts in r1
        for (int j = 0; j < r2->facts.size(); j++) { //Loop through the facts in r2
            Tuple* t = new Tuple(r1->facts.at(i)->values); //Start with the fact in r1
            for (int k = 0; k < r2->facts.at(j)->values.size(); k++) { //Loop through the values of the fact in r2
                t->values.push_back(r2->facts.at(j)->values.at(k)); //Add the values to the fact in r1
            }
            newRelation->facts.push_back(t);
        }
    }
    
    return newRelation;
}

Relation* Database::getHeadRelation(Rule* rule) {
    Relation* headRelation = NULL;
    for (int i = 0; i < relations.size(); i++) { //Loop through the relations
        if (rule->first->getTokensValue().compare(relations.at(i)->name) == 0) { //If the rule head matches the name of the relation
            headRelation = relations.at(i);
            break;
        }
    }
    return headRelation;
}

std::vector<Relation*> Database::getRelationList(std::vector<Predicate*> predicateList) {
    std::vector<Relation*> relationList;
    for (int i = 0; i < predicateList.size(); i++) { //Loop through the list of predicates
        
        //Create a new relation from each entry in the list
        Relation* r = NULL;
        std::string name = predicateList.at(i)->first->getTokensValue();
        for (int j = 0; j < relations.size(); j++) { //Loop through the list of relations
            if (name.compare(relations.at(j)->name) == 0) { //If a match is found
                r = relations.at(j)->copy(); //Copy the relation
                break;
            }
        }
        
        r = r->processQuery(predicateList.at(i)->parl); //Treat the predicate as a query
        relationList.push_back(r); //Add the relation to the list
    }
    return relationList;
}

std::vector<std::string> Database::getHeadVariables(std::vector<Token*> headParameterList) {
    std::vector<std::string> headVariables;
    for (int i = 0; i < headParameterList.size(); i++) {
        headVariables.push_back(headParameterList.at(i)->getTokensValue());
    }
    return headVariables;
}

Relation* Database::renameToMatch(Relation* headRelation, Relation* newRelation, std::vector<std::string> headVariables) {
    for (int i = 0; i < newRelation->columns->attributes.size(); i++) {
        for (int j = 0; j < headVariables.size(); j++) {
            if (newRelation->columns->attributes.at(i).compare(headVariables.at(j)) == 0) {
                newRelation = newRelation->rename(newRelation->columns->attributes.at(i), headRelation->columns->attributes.at(j));
            }
        }
    }
    
    return newRelation;
}

Relation* Database::unionWith(Relation* r1, Relation* r2) {
    Relation* newRelation = r1; //Start with the first relation
    
    for (int i = 0; i < r2->facts.size(); i++) { //Loop through the facts of the second relation
        Tuple* t = new Tuple();
        for (int j = 0; j < r1->columns->attributes.size(); j++) {
            std::string a1 = r1->columns->attributes.at(j);
            for (int k = 0; k < r2->columns->attributes.size(); k++) {
                std::string a2 = r2->columns->attributes.at(k);
                if (a1.compare(a2) == 0) {
                    t->values.push_back(r2->facts.at(i)->values.at(k));
                }
            }
        }
        
        bool duplicate = false;
        for (int j = 0; j < newRelation->facts.size(); j++) {
            if (t->compare(newRelation->facts.at(j)) == 0) {
                duplicate = true;
            }
        }
        
        if (!duplicate) {
            newRelation->facts.push_back(t);
            std::sort(newRelation->facts.begin(), newRelation->facts.begin(), Relation::tupleCompare);
        }
    }
    
    return newRelation;
}

int Database::getNumFacts() {
    int size = 0;
    for (int i = 0; i < relations.size(); i++) { //Loop through all the relations
        size += relations.at(i)->facts.size(); //Add up the number of facts in all the relations
    }
    return size;
}