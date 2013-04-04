//
//  Pair.cpp
//  Project3
//
//  Created by Connor Smith on 3/16/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#include "Pair.h"

Pair::Pair() {
    attribute = "";
    value = "";
}

Pair::Pair(std::string attr, std::string val) {
    attribute = attr;
    value = val;
}

Pair::~Pair() {
    
}

bool Pair::compare(Pair p) {
    return (attribute == p.attribute && value == p.value);
}