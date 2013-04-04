//
//  Schema.cpp
//  Project3
//
//  Created by Connor Smith on 3/14/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#include "Schema.h"

Schema::Schema () {
    
}

Schema::Schema (std::vector<Token*> attrs) {
    for (int i = 0; i < attrs.size(); i++) {
        attributes.push_back(attrs.at(i)->getTokensValue());
    }
}

Schema::~Schema() {
    
}

Schema* Schema::copy() {
    Schema* s = new Schema();
    for (int i = 0; i < attributes.size(); i++)
        s->attributes.push_back(attributes.at(i));
    return s;
}

std::string Schema::print() {
    std::string s = "";
    s += "(";
    for (int i = 0; i < attributes.size(); i++) {
        s += attributes.at(i);
        if (i < attributes.size() - 1) {
            s += ",";
        }
    }
    s += ")";
    return s;
}
