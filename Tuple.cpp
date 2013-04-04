//
//  Tuple.cpp
//  Project3
//
//  Created by Connor Smith on 3/14/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#include "Tuple.h"

Tuple::Tuple () {
    
}

Tuple::Tuple (std::vector<std::string> vals) {
    values = vals;
}

Tuple::~Tuple() {
    
}

int Tuple::compare(Tuple* t) {
    for (int i = 0; i < values.size(); i++) { //Loop through all the values in the tuple
        if (values.at(i).compare(t->values.at(i)) != 0) //If any value differs, they are not the same
            return 1;
    }
    return 0; //If all values are the same, return that they are
}

std::string Tuple::print(Schema* columns) {
    std::string s = "";
    for (int i = 0; i < values.size(); i++) {
        s += columns->attributes.at(i) + "=" + values.at(i);
        if (i < values.size() - 1) {
            s += ", ";
        }
    }
    return s;
}