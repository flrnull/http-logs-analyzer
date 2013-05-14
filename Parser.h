#ifndef PARSER_H
#define	PARSER_H

#include "Config.h"

class Parser 
{
public:
    Parser(Config *config);
    ~Parser();
    bool parse(std::string logLine);
private:
    Config *config;
};


#endif	/* PARSER_H */

