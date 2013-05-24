#ifndef RESULT_H
#define	RESULT_H

#include <map>

namespace Result
{
    // Result values
    extern unsigned int views;
    extern unsigned int visitors;
    extern unsigned int urls;
    extern unsigned int traffic;
    extern unsigned int lines;
    extern unsigned int fails;
    // Temp values
    extern std::map<std::string,int> ipAgentMap;
    extern std::map<std::string,int> urlMap;
    // Actions
    void display();
};
  

#endif	/* RESULT_H */

