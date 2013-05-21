#ifndef PARSER_H
#define	PARSER_H

#include "Config.h"
#include "regex_functions.h"

class Parser 
{
public:
    Parser(Config *config);
    ~Parser();
    bool parse(std::string logLine, LogRegexCompiled *logRegExpsCompiled);
private:
    Config *config;
};


#endif	/* PARSER_H */

