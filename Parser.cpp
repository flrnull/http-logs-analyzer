#include "Parser.h"
#include "Debug.h"
#include "Config.h"
#include <iostream>
#include "regex_functions.h"

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
    regex_t regex;
    const char * regexText;
    const char * findText;
    regexText = "[0-9]{3,}";
    findText = "Test a124 test";
    std::string regexStr(regexText);
    std::string findStr(findText);
    Debug::print("Trying to find /" + regexStr + "/ in " + findStr);
    compileRegex(&regex, regexText);
    matchRegex(&regex, findText);
    regfree (&regex);
    return true;
}
