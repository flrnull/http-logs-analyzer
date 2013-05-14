#include "Parser.h"
#include "Debug.h"
#include "Config.h"
#include <iostream>

Parser::Parser(Config *config)
: config(config)
{
    if (config->debugMode == 1) {
        Debug::print("(Parser constructor)");
    }
}

Parser::~Parser() {
    if (config->debugMode == 1) {
        Debug::print("(Parser constructor)");
    }
}

bool Parser::parse(std::string logLine) {
    
    return true;
}
