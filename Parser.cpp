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
    } else {
        // Parse search engines scan
        const char * agentChars = agentRes.c_str();
        if (config->debugMode == 1) {
            Debug::print("Parser::parse: trying to found " + std::string(GOOGLE_PATTERN) + " in agent" + agentRes);
        }
        std::string googleRes = matchRegex(&(*logRegExpsCompiled).google, agentChars, config);
        if (googleRes.length() > 3) {
            Result::google++;
        } else {
            if (config->debugMode == 1) {
                Debug::print("Parser::parse: trying to found " + std::string(BING_PATTERN) + " in agent" + agentRes);
            }
            std::string bingRes = matchRegex(&(*logRegExpsCompiled).bing, agentChars, config);
            if (bingRes.length() > 3) {
                Result::bing++;
            } else {
                if (config->debugMode == 1) {
                    Debug::print("Parser::parse: trying to found " + std::string(BAIDU_PATTERN) + " in agent" + agentRes);
                }
                std::string baiduRes = matchRegex(&(*logRegExpsCompiled).baidu, agentChars, config);
                if (baiduRes.length() > 3) {
                    Result::baidu++;
                } else {
                    if (config->debugMode == 1) {
                        Debug::print("Parser::parse: trying to found " + std::string(YANDEX_PATTERN) + " in agent" + agentRes);
                    }
                    std::string yandexRes = matchRegex(&(*logRegExpsCompiled).yandex, agentChars, config);
                    if (yandexRes.length() > 3) {
                        Result::yandex++;
                    }
                }
            }
        }
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
        std::string agentResLength = ss.str();
        std::string mapKey = ipRes + agentResLength;
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
        std::string urlMapKey = urlRes;
        std::map<std::string,int>::iterator itUrl;
        itUrl = Result::urlMap.find(urlMapKey);
        if (itUrl == Result::urlMap.end()) {
            if (config->debugMode == 1) {
                Debug::print("Parser::parse: url " + urlMapKey + " is not in our reesult list, added");
            }
            Result::urlMap[urlMapKey] = 1;
        } else {
            if (config->debugMode == 1) {
                Debug::print("Parser::parse: url " + urlMapKey + " is already in our reesult list, increment");
            }
            itUrl->second++;
        }
        // Add URL to top URLs
        int urlCount = (itUrl == Result::urlMap.end()) ? 1 : itUrl->second;
        Result::topUrlTryToAdd(urlMapKey, urlCount, config);
    }
    
    // Parse referer
    if (config->debugMode == 1) {
        Debug::print("Parser::parse: trying to found referer");
    }
    std::string refRes = matchRegex(&(*logRegExpsCompiled).referer, logLineChars, config);
    if (refRes.length() < 1) {
        Result::fails++;
        return false;
    } else {
        // Save to URLs map for calc uniq URLs
        std::string refMapKey = refRes;
        std::map<std::string,int>::iterator itRef;
        itRef = Result::refsMap.find(refMapKey);
        if (itRef == Result::refsMap.end()) {
            if (config->debugMode == 1) {
                Debug::print("Parser::parse: url " + refMapKey + " is not in our reesult list, added");
            }
            Result::refsMap[refMapKey] = 1;
        } else {
            if (config->debugMode == 1) {
                Debug::print("Parser::parse: url " + refMapKey + " is already in our reesult list, increment");
            }
            itRef->second++;
        }
        // Add URL to top URLs
        int refCount = (itRef == Result::refsMap.end()) ? 1 : itRef->second;
        Result::topRefsTryToAdd(refMapKey, refCount, config);
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
