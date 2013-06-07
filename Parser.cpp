#include "Parser.h"
#include "Debug.h"
#include "Config.h"
#include <iostream>
#include "regex_functions.h"
#include "Result.h"
#include <sstream>
#include "common_functions.h"

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
    const char * logLineChars = logLine.c_str();
    if (config->debugMode == 1) {
        Debug::print("Parser::parse: logLine = " + logLine);
    }
    
    // For each line
    Result::lines++;
    
    // Parse Agent
    if (config->debugMode == 1) {
        Debug::print("Parser::parse: trying to found agent");
    }
    std::string agentRes = matchRegex(&(*logRegExpsCompiled).agent, logLineChars, config);
    if (agentRes.length() < 5) {
        Result::fails++;
        return false;
    }
    
    // Parse IP
    if (config->debugMode == 1) {
        Debug::print("Parser::parse: trying to found ip");
    }
    std::string ipRes = matchRegex(&(*logRegExpsCompiled).ip, logLineChars, config);
    if (ipRes.length() < 5) {
        Result::fails++;
        return false;
    } else {
        // Save to IPs map for calc uniq visitors
        std::ostringstream ss;
        ss << agentRes.length();
        std::string agentResCount = ss.str();
        std::string mapKey = ipRes + agentResCount;
        std::map<std::string,int>::iterator it;
        it = Result::ipAgentMap.find(mapKey);
        if (it == Result::ipAgentMap.end()) {
            Result::ipAgentMap[mapKey] = 1;
        } else {
            it->second++;
        }
    }
    
    // Parse url
    if (config->debugMode == 1) {
        Debug::print("Parser::parse: trying to found url");
    }
    std::string urlRes = matchRegex(&(*logRegExpsCompiled).url, logLineChars, config);
    if (urlRes.length() < 1) {
        Result::fails++;
        return false;
    } else {
        // Save to URLs map for calc uniq URLs
        std::ostringstream sss;
        sss << urlRes.length();
        std::string urlResCount = sss.str();
        std::string urlMapKey = ipRes + urlResCount;
        std::map<std::string,int>::iterator it;
        it = Result::urlMap.find(urlMapKey);
        if (it == Result::urlMap.end()) {
            Result::urlMap[urlMapKey] = 1;
        } else {
            it->second++;
        }
    }
    
    // Parse traffic
    if (config->debugMode == 1) {
        Debug::print("Parser::parse: trying to found traffic");
    }
    std::string trafficRes = matchRegex(&(*logRegExpsCompiled).traffic, logLineChars, config);
    if (trafficRes.length()) {
        if (config->debugMode == 1) {
            Debug::print("Parser::parse: trafficRes: " + trafficRes);
        }
        int traffic = 0;
        traffic = StringToNumber(trafficRes, 0);
        Result::traffic += traffic;
    }
    
    // For each success line
    Result::views++;
    return true;
}
