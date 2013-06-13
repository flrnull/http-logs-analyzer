#include "Result.h"
#include "Debug.h"
#include <iostream>

unsigned int Result::views = 0;
unsigned int Result::visitors = 0;
unsigned int Result::urls = 0;
unsigned long Result::traffic = 0;
unsigned int Result::lines = 0;
unsigned int Result::fails = 0;
unsigned int Result::google = 0;
unsigned int Result::bing = 0;
unsigned int Result::baidu = 0;
unsigned int Result::yandex = 0;
std::map<std::string,int> Result::topUrlMap;


std::map<std::string,int> Result::ipAgentMap;
std::map<std::string,int> Result::urlMap;

void Result::display() {
    std::cout << "{" << std::endl;
    std::cout << "  views: " << Result::views << "," << std::endl;
    std::cout << "  visitors: " << Result::visitors << "," << std::endl;
    std::cout << "  urls: " << Result::urls << "," << std::endl;
    std::cout << "  traffic: " << Result::traffic << "," << std::endl;
    std::cout << "  lines: " << Result::lines << "," << std::endl;
    std::cout << "  fails: " << Result::fails << "," << std::endl;
    std::cout << "  crawlers: {" << std::endl;
    std::cout << "      Google: " << Result::google << "," << std::endl;
    std::cout << "      Bing: " << Result::bing << "," << std::endl;
    std::cout << "      Baidu: " << Result::baidu << "," << std::endl;
    std::cout << "      Yandex: " << Result::yandex << std::endl;
    std::cout << "  }," << std::endl;
    std::cout << "  topUrls: {" << std::endl;
    typedef std::map<std::string,int>::const_iterator UrlMapIterator;
    for (UrlMapIterator it = Result::topUrlMap.begin(); it != Result::topUrlMap.end(); it++) {
        std::cout << "      " << it->first << ": " << it->second;
        if (it != Result::topUrlMap.end()) {
            std::cout << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "  }" << std::endl;
    std::cout << "}" << std::endl;
}

void Result::topUrlTryToAdd(std::string urlMapKey, int count, Config * config) {
    if (config->debugMode) {
        Debug::print("Result::topUrlTryToAdd: calc started");
    }
    // First item add to top
    int topCount = Result::topUrlMap.size();
    std::map<std::string,int>::iterator itRes;
    bool isAdded, isDeleted;
    std::string tempUrl;
    int tempCount;
    if (!topCount) {
        if (config->debugMode) {
            Debug::print("Result::topUrlTryToAdd: first element is added " + urlMapKey);
        }
        Result::topUrlMap[urlMapKey] = count;
        return;
    } else {
        itRes = Result::topUrlMap.begin();
        isAdded = false;
        isDeleted = false;
        // Go through current top from the largest to the smallest
        // First element in top should be the largest
        for(int j = 0; j < topCount && !isAdded; j++) {
            std::advance(itRes, j);
            // If current value bigger than in top we add it
            if (count > itRes->second) {
                if (config->debugMode) {
                    Debug::print("Result::calcTopUrls: " + urlMapKey + " count is bigger");
                }
                Result::topUrlMap[urlMapKey] = count;
                topCount++;
                isAdded = true;
            }
        }
        // If topUrl exceed limit we should remove the smallest
        tempUrl = "";
        tempCount = 0;
        if (isAdded && topCount > config->topUrlsCount) {
            for(int z = 0; z < topCount && !isDeleted; z++) {
                std::advance(itRes, z);
                if (itRes->second < tempCount && tempCount) {
                    // we save smallest values to temp params
                    tempUrl = itRes->first;
                    tempCount = itRes->second;
                }
            }
            // delete saved temp param
            if (tempCount) {
                if (config->debugMode) {
                    Debug::print("Result::calcTopUrls: remove the smallest url " + tempUrl);
                }
                Result::topUrlMap.erase(tempUrl);
            }
        }
    }
}

void Result::calcTopUrls(Config * config) {
    if (config->debugMode) {
        Debug::print("Result::calcTopUrls: calc started");
    }
    std::map<std::string,int>::iterator it = Result::urlMap.begin();
    std::map<std::string,int>::iterator itRes = Result::topUrlMap.begin();
    int urlMapSize = Result::urlMap.size();
    int topCount = 0;
    bool isAdded, isDeleted;
    std::string tempUrl;
    int tempCount;
    for(int i = 0; i < urlMapSize; i++) {
        // First item add to top
        if (!topCount) {
            if (config->debugMode) {
                Debug::print("Result::calcTopUrls: first element is added " + it->first);
            }
            Result::topUrlMap[it->first] = it->second;
            topCount++;
        } else {
            std::advance(it, i);
            // If we already have any urls in top
            if (topCount) {
                isAdded = false;
                isDeleted = false;
                // Go through current top from the largest to the smallest
                // First element in top should be the largest
                for(int j = 0; j < topCount && !isAdded; j++) {
                    std::advance(itRes, j);
                    // If current value bigger than in top we add it
                    if (it->second > itRes->second) {
                        if (config->debugMode) {
                            Debug::print("Result::calcTopUrls: " + it->first + " count is bigger");
                        }
                        Result::topUrlMap[it->first] = it->second;
                        topCount++;
                        isAdded = true;
                    }
                }
                // If topUrl exceed limit we should remove the smallest
                tempUrl = "";
                tempCount = 0;
                if (isAdded && topCount > config->topUrlsCount) {
                    for(int z = 0; z < topCount && !isDeleted; z++) {
                        std::advance(itRes, z);
                        if (itRes->second < tempCount && tempCount) {
                            // we save smallest values to temp params
                            tempUrl = itRes->first;
                            tempCount = itRes->second;
                        }
                    }
                    // delete saved temp param
                    if (tempCount) {
                        if (config->debugMode) {
                            Debug::print("Result::calcTopUrls: remove the smallest url " + tempUrl);
                        }
                        Result::topUrlMap.erase(tempUrl);
                    }
                }
            }
        }
    }
}
