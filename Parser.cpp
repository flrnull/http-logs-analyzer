#include "Parser.h"
#include "Debug.h"
#include "Config.h"
#include <iostream>
#include "regex_functions.h"

Parser::Parser(Config *config)
: config(config)
{
    if (config->debugMode == 1) {
        Debug::print("<Parser constructor>");
    }
}

Parser::~Parser() {
    if (config->debugMode == 1) {
        Debug::print("</Parser destructor>");
    }
}

bool Parser::parse(std::string logLine, LogRegexCompiled *logRegExpsCompiled) {
    const char * findText = logLine.c_str();
    if (config->debugMode == 1) {
        Debug::print("Parser::parse: logLine = " + logLine);
    }
    matchRegex(&(*logRegExpsCompiled).ip, findText, config);
    return true;
}
