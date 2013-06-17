#ifndef RESULT_H
#define	RESULT_H

#include <map>
#include <string>
#include "Config.h"

namespace Result
{
    // Result values
    extern unsigned int views;
    extern unsigned int visitors;
    extern unsigned int urls;
    extern unsigned long traffic;
    extern unsigned int lines;
    extern unsigned int fails;
    extern unsigned int google;
    extern unsigned int bing;
    extern unsigned int baidu;
    extern unsigned int yandex;
    extern std::map<std::string,int> topUrlMap;
    extern std::map<std::string,int> topRefsMap;
    extern std::map<std::string,int> codesMap;
    // Temp values
    extern std::map<std::string,int> ipAgentMap;
    extern std::map<std::string,int> urlMap;
    extern std::map<std::string,int> refsMap;
    // Actions
    void display();
    void topUrlTryToAdd(std::string urlMapKey, int count, Config * config);
    void topRefsTryToAdd(std::string refsMapKey, int count, Config * config);
};
  

#endif	/* RESULT_H */

