//
//  Schema.h
//  Project3
//
//  Created by Connor Smith on 3/14/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#ifndef __Project3__Schema__
#define __Project3__Schema__

#include <iostream>
#include <vector>

#include "Token.h"

class Schema {
public:
    std::vector<std::string> attributes;
    
    Schema();
    Schema(std::vector<Token*> attrs);
    ~Schema();
    Schema* copy();
    std::string print();
};

#endif /* defined(__Project3__Schema__) */
