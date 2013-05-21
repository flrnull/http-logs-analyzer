#include "Parser.h"
#include "Debug.h"
#include "Config.h"
#include <iostream>
#include "regex_functions.h"
#include "Result.h"

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
    // For each line
    Result::lines++;
    // Parse IP
    std::string ipRes = matchRegex(&(*logRegExpsCompiled).ip, findText, config);
    if (ipRes.length() < 4) {
        Result::fails++;
        return false;
    } else {
        
    }
    
    // For each success line
    Result::views++;
    return true;
}
