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
    int topUrlMapSize = Result::topUrlMap.size();
    int iteration = 0;
    for (UrlMapIterator it = Result::topUrlMap.begin(); it != Result::topUrlMap.end(); it++) {
        iteration++;
        std::cout << "      " << it->first << ": " << it->second;
        if (iteration < topUrlMapSize) {
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
    typedef std::map<std::string,int>::const_iterator mapIterator;
    mapIterator itRes;
    bool isAdded;
    std::string tempUrl;
    int tempCount;
    if (!topCount) {
        if (config->debugMode) {
            Debug::print("Result::topUrlTryToAdd: first element is added " + urlMapKey);
        }
        Result::topUrlMap[urlMapKey] = count;
        return;
    } else {
        if (config->debugMode) {
            Debug::print("Result::topUrlTryToAdd: try to add element " + urlMapKey);
        }
        
        if (Result::topUrlMap.find(urlMapKey) != Result::topUrlMap.end()) {
            if (config->debugMode) {
                Debug::print("Result::topUrlTryToAdd: element is not deleted, because it duplicated " + tempUrl);
            }
            Result::topUrlMap[urlMapKey] = count;
            return;
        }
        
        itRes = Result::topUrlMap.begin();
        isAdded = false;
        // Go through current top from the largest to the smallest
        // First element in top should be the largest
        for(int j = 0; (j < topCount) && !isAdded; j++) {
            std::advance(itRes, j);
            // If current value bigger than in top we add it
            if ((count > itRes->second) || (topCount < config->topUrlsLimit)) {
                if (config->debugMode) {
                    Debug::print("Result::topUrlTryToAdd: " + urlMapKey + " count is bigger");
                    Debug::print(count);
                    Debug::print(itRes->second);
                }
                Result::topUrlMap[urlMapKey] = count;
                topCount++;
                isAdded = true;
            } else {
                if (config->debugMode) {
                    Debug::print("Result::topUrlTryToAdd: count is smaller");
                    Debug::print(count);
                    Debug::print(itRes->second);
                }
            }
        }
        // If topUrl exceed limit we should remove the smallest
        tempUrl = "";
        tempCount = 0;
        
        if (isAdded && (topCount > config->topUrlsLimit)) {
            if (config->debugMode) {
                Debug::print("Result::topUrlTryToAdd: topCount is bigger than topUrlsLimit");
            }
            for (mapIterator iterTop = Result::topUrlMap.begin(); iterTop != Result::topUrlMap.end(); iterTop++) {
                if ((iterTop->second < tempCount) || !tempCount) {
                    // we save smallest values to temp params
                    if (config->debugMode) {
                        Debug::print("Result::topUrlTryToAdd: we save smallest values to temp params: " + iterTop->first);
                    }
                    tempUrl = iterTop->first;
                    tempCount = iterTop->second;
                } else {
                    if (config->debugMode) {
                        Debug::print("Result::topUrlTryToAdd: false return by if (itRes->second < tempCount) && tempCount");
                    }
                }
            }
            // delete saved temp param
            if (tempCount) {
                std::map<std::string,int>::iterator removeIt = Result::topUrlMap.find(tempUrl);
                if (config->debugMode) {
                    Debug::print("Result::topUrlTryToAdd: remove the smallest url: " + tempUrl);
                }
                Result::topUrlMap.erase(removeIt);
            }
        } else {
            if (config->debugMode) {
                int isAddedNum = (isAdded) ? 1 : 0;
                Debug::print("Result::topUrlTryToAdd: element is not deleted, because nothing was added or top count is under limits");
                Debug::print("Result::topUrlTryToAdd: topCocount: ");
                Debug::print(topCount);
                Debug::print("Result::topUrlTryToAdd: isAdded is: ");
                Debug::print(isAddedNum);
            }
        }
        
    }
}
