//
//  main.cpp
//  Project3
//
//  Created by Connor Smith on 3/16/13.
//  Copyright (c) 2013 Connor Smith. All rights reserved.
//

#include "Lex.h"
#include "DatalogProgram.h"
#include "Database.h"

int main(int argc, char* argv[]) {
    Lex lex(argv[1]); //Lex the input
    
    DatalogProgram* parser = new DatalogProgram(lex.tokens); //Create the parser
    parser->parse(); //Parse the input
    
    Database* database = new Database(parser); //Create the database
    database->processQueries(); //Process the queries
    
    return 0;
}