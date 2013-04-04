//
//  Pair.h
//  Project3
//
//  Created by Connor Smith on 3/16/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#ifndef __Project3__Pair__
#define __Project3__Pair__

#include <iostream>

class Pair {
public:
    std::string attribute;
    std::string value;
    
    Pair();
    Pair(std::string attr, std::string val);
    ~Pair();
    bool compare(Pair p);
};

#endif /* defined(__Project3__Pair__) */
