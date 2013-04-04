//
//  Relation.cpp
//  Project3
//
//  Created by Connor Smith on 3/14/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#include "Relation.h"

Relation::Relation () {
    name = "";
    columns = new Schema();
}

Relation::Relation (Token* n, std::vector<Token*> schema) {
    name = n->getTokensValue();
    columns = new Schema(schema);
}

Relation::~Relation() {
    delete columns;
    for (int i = 0; i < facts.size(); i++)
        delete facts.at(i);
}

void Relation::addTuple(Fact* f) {
    Tuple* t = new Tuple(f->cl);
    for (int i = 0; i < facts.size(); i++) { //Loop through all facts
        if (t->compare(facts.at(i)) == 0) { //If a duplicate is found
            return;
        }
    }
    
    facts.push_back(new Tuple(f->cl)); //Add the new fact
    
    std::sort(facts.begin(), facts.end(), tupleCompare); //Sort the list of facts
}

bool Relation::tupleCompare(Tuple* t1, Tuple*t2) {
    for (int i = 0; i < t1->values.size(); i++) { //Loop through the list of values
        if (t1->values.at(i).compare(t2->values.at(i)) < 0) //If the first tuple's value is less, return less
            return true;
        else if (t1->values.at(i).compare(t2->values.at(i)) > 0) //If the first tuple's value is greater, return greater
            return false;
    } //Otherwise, go on to the next value
    
    return false; //If the two tuples are identical (shouldn't ever happen), return less
}

Relation* Relation::processQuery(std::vector<Parameter*> args) {
    Relation* newRelation = copy();
        
    //Select on constants
    for (int i = 0; i < args.size(); i++) { //Loop through the query's argument list
        if (args.at(i)->content.at(0)->getTokenType() == STRING) { //If the current argument is a string (a constant)
            std::string attribute = newRelation->columns->attributes.at(i); //Get the attribute name of the constant
            std::string value = args.at(i)->content.at(0)->getTokensValue(); //Get the value of the constant
            newRelation = newRelation->selectConstant(new Pair(attribute, value)); //Select out facts matching the attribute-value pair
        }
    }
    
    std::vector<std::string> columnList;

    //If the same variable repeats

    //Select, equating the attribute names for the arguments
    std::vector<std::pair<std::string, std::vector<int> > > vars;
    for (int i = 0; i < args.size(); i++) { //Loop through the list of arguments
        if (args.at(i)->content.at(0)->getTokenType() == ID) { //If the current argument is an ID (a variable)
            std::string temp = args.at(i)->content.at(0)->getTokensValue(); //Store its value
            
            bool found = false;
            for (int j = 0; j < vars.size(); j++) { //Loop through the list of unique variables
                if (temp.compare(vars.at(j).first) == 0) { //If the current variable is already in the vector
                    found = true; //Mark found
                    vars.at(j).second.push_back(i); //Add the index to the list of attributes with the same variable
                }
            }
            
            if (!found) { //If the current variable is not in the vector
                std::vector<int> v;
                v.push_back(i);
                std::pair<std::string, std::vector<int> > p(temp, v);
                vars.push_back(p);
            }
        }
    }
        
    for (int i = 0; i < vars.size(); i++) {
        newRelation = newRelation->selectVariables(vars.at(i).second);
    }
    
    
    //Project on all but one of the attributes
    for (int i = 0; i < vars.size(); i++) { //Loop through all of the variables
        std::string s = newRelation->columns->attributes.at(vars.at(i).second.at(0)); //Add only one occurence of each variable
        columnList.push_back(s);
    }
    
    newRelation = newRelation->project(columnList); //Project on all variables
        
    //Rename attributes to match the query's variable names
    for (int i = 0; i < newRelation->columns->attributes.size(); i++) { //Loop through the argument list
        std::string oldAttr = newRelation->columns->attributes.at(i); //Get the corresponding attribute name from the schema
        std::string newAttr = vars.at(i).first; //Get the variable name
        newRelation = newRelation->rename(oldAttr, newAttr); //Rename the attribute to the variable name
    }
        
    //Project on the set of variable names in the query
    columnList.clear();
    for (int i = 0; i < args.size(); i++) { //Loop through the argument list
        Token* arg = args.at(i)->content.at(0);
        if (arg->getTokenType() == ID) { //If the current argument is an ID (a variable)
            columnList.push_back(arg->getTokensValue()); //Add the variable name to the projected columns
        }
    }
    
    return newRelation;
}

Relation* Relation::project(std::vector<std::string> columnList){
    Relation* newRelation = copy(); //Start with the current relation
        
    bool includePositions [newRelation->columns->attributes.size()];
    for (int i = 0; i < newRelation->columns->attributes.size(); i++) { //Loop through the list of attributes
        includePositions[i] = false;
        
        for (int j = 0; j < columnList.size(); j++) { //Loop through the list of columns to project on
            if (newRelation->columns->attributes.at(i).compare(columnList.at(j)) == 0) { //If the current column is in the list to project on
                includePositions[i] = true; //Include it
            }
        }
    }
    
    int pos = 0;
    for (int i = 0; i < newRelation->columns->attributes.size(); i++) { //Loop through the attributes of the relation
        if (!includePositions[pos]) { //If the current column isn't in the list of columns to project on
            newRelation->columns->attributes.erase(newRelation->columns->attributes.begin() + i); //Erase the column
            i--; //Decrement the position (don't skip over the next column)
        }
        pos++;
    }
        
    for (int i = 0; i < newRelation->facts.size(); i++) { //Loop through the facts of the relation
        int pos = 0;
        for (int j = 0; j < newRelation->facts.at(i)->values.size(); j++) { //Loop through the attributes of each fact
            if (!includePositions[pos]) { //If the current column is not in the list of columns to project on
                newRelation->facts.at(i)->values.erase(newRelation->facts.at(i)->values.begin() + j); //Erase it
                j--; //Decrement the iterator (don't skip over the next column)
            }
            pos++;
        }
    }
        
    return newRelation; //Return the modified relation
}

Relation* Relation::rename(std::string oldAttr, std::string newAttr){
    Relation* newRelation = copy(); //Start with the current relation
    
    for (int i = 0; i < newRelation->columns->attributes.size(); i++) { //Loop through the attributes of the relation
        if (newRelation->columns->attributes.at(i).compare(oldAttr) == 0) { //If the target attribute is found
            newRelation->columns->attributes.at(i) = newAttr; //Rename the target attribute to the new attribute
            break;
        }
    }
    
    return newRelation; //Return the modified relation
}

Relation* Relation::selectConstant(Pair* p){
    Relation* newRelation = copy(); //Start with the current relation
    
    int pos = -1;
    for (int i = 0; i < newRelation->columns->attributes.size(); i++) { //Loop through the attributes of the relation
        if (newRelation->columns->attributes.at(i) == p->attribute) { //If the pair's attribute matches the current attribute of the relation
            pos = i; //Store the index of the attribute
        }
    }
    if (pos == -1) //If the attribute wasn't found
        return newRelation; //Return the unmodified relation
    
    for (int i = 0; i < newRelation->facts.size(); i++) { //Loop through the list of facts
        if (newRelation->facts.at(i)->values.at(pos) != p->value) { //If the current fact's value does not match the pair's value
            newRelation->facts.erase(newRelation->facts.begin() + i); //Remove the fact
            i--; //Decrement the iterator (don't skip the next fact)
        }
    }
    
    return newRelation; //Return the modified relation
}

Relation* Relation::selectVariables(std::vector<int> vars) {
    Relation* newRelation = copy(); //Start with the current relation
    
    for (int i = 0; i < newRelation->facts.size(); i++) { //Loop through the list of facts
        //std::string baseValue = newRelation->facts.at(i)->values.at(0);
        std::string baseValue = newRelation->facts.at(i)->values.at(vars.at(0));
        for (int j = 0; j < vars.size(); j++) { //Loop through the list of free variables
            if (newRelation->facts.at(i)->values.at(vars.at(j)).compare(baseValue) != 0) { //If the current attribute's value does not match the base value
                newRelation->facts.erase(newRelation->facts.begin() + i); //Remove the current fact
                i--; //Decrement the iterator (don't skip the next fact)
                break;
            }
        }
    }
    
    return newRelation; //Return the modified relation
}

Relation* Relation::copy() {
    Relation* r = new Relation();
    r->name = name;
    r->columns = columns->copy();
    for (int i = 0; i < facts.size(); i++) {
        r->facts.push_back(new Tuple(facts.at(i)->values));
    }
    return r;
}

std::string Relation::print(std::vector<Parameter*> args) {
    std::stringstream s;
    s << name << "(";
    for (int i = 0; i < args.size(); i++) {
        s << args.at(i)->content.at(0)->getTokensValue();
        if (i < args.size() - 1)
            s << ",";
    }
    s << ")? ";
    if (facts.size() == 0) {
        s << "No\n";
        return s.str();
    }
    s << "Yes(" << facts.size() << ")\n";
    
    if (columns->attributes.size() == 0)
        return s.str();
    
    for (int i = 0; i < facts.size(); i++) {
        s<<"  "<<facts.at(i)->print(columns)<<"\n";
    }
    return s.str();
}
