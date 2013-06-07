#include "Config.h"
#include "Debug.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>

Config* Config::_instance = 0;

// Current default config
Config::Config()
    : logName("./example/access_log")
    , debugMode(0)
    , ipPattern("")
    , agentPattern("")
    , urlPattern("")
    , trafficPattern("")
{
    if (this->debugMode == 1) {
        Debug::print("<Config constructor>");
    }
}

Config::~Config() {
    if (this->debugMode == 1) {
        Debug::print("</Config destructor>");
    }
}

Config * Config::getInstance() {
    if (!_instance) {
        _instance = new Config();
    }
    return _instance;
}

void Config::parseArgs(int argc, char **argv) {
    int c;
    while ((c = getopt(argc, argv, "df:i:a:u:t:")) != -1) {
        switch(c) {
            case 'f':
                this->logName = optarg;
                break;
            case 'd':
                this->debugMode = 1;
                break;
            // Patterns
            case 'i':
                this->ipPattern = optarg;
                break;
            case 'a':
                this->agentPattern = optarg;
                break;
            case 'u':
                this->urlPattern = optarg;
                break;
            case 't':
                this->trafficPattern = optarg;
                break;    
            case '?':
                if (optopt == 'f') {
                    exit(1);
                }
                if (optopt == 'i') {
                    exit(1);
                }
                if (optopt == 'a') {
                    exit(1);
                }
                if (optopt == 'u') {
                    exit(1);
                }
                if (optopt == 't') {
                    exit(1);
                }
                break;
        }
    }
}

void Config::debug() {
    if (this->debugMode == 1) {
        std::string debugString;
        std::stringstream sstm;
        sstm << "----> debugMode: " << this->debugMode;
        debugString = sstm.str();
        
        Debug::print("Options:");
        Debug::print(debugString);
        Debug::print("----> logName: " + this->logName);
    }
}

