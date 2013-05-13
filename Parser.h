#ifndef PARSER_H
#define	PARSER_H

#include "Config.h"

class Parser 
{
public:
    Parser(std::auto_ptr<Config> config);
    ~Parser();
private:
    std::auto_ptr<Config> config;
};


#endif	/* PARSER_H */

