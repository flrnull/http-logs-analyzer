#include "Parser.h"
#include "Debug.h"
#include "Config.h"
#include <iostream>

Parser::Parser(std::auto_ptr<Config> config)
: config(config)
{
    if (this->config->debugMode == 1) {
        Debug::print("(Parser constructor)");
    }
}

Parser::~Parser() {
    if (this->config->debugMode == 1) {
        Debug::print("(Parser constructor)");
    }
}
