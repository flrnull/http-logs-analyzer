#include "Config.h"
#include "Debug.h"
#include "Patterns.h"
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
    , refPattern("")
    , topUrlsLimit(10)
    , topRefsLimit(10)
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
    while ((c = getopt(argc, argv, "dhf:i:a:u:t:")) != -1) {
        switch(c) {
            case 'd':
                this->debugMode = 1;
                break;
            case 'h':
                Config::help();
                exit(0);
                break;
            case 'f':
                this->logName = optarg;
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
            case 'r':
                this->refPattern = optarg;
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
                if (optopt == 'r') {
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
        Debug::print("----> ipPattern: " + (this->ipPattern.length() ? this->ipPattern : IP_PATTERN));
        Debug::print("----> trafficPattern: " + (this->trafficPattern.length() ? this->trafficPattern : TRAFFIC_PATTERN));
        Debug::print("----> urlPattern: " + (this->urlPattern.length() ? this->urlPattern : URL_PATTERN));
        Debug::print("----> agentPattern: " + (this->agentPattern.length() ? this->agentPattern : AGENT_PATTERN));
        Debug::print("----> refPattern: " + (this->refPattern.length() ? this->refPattern : REF_PATTERN));
        Debug::print("----> topUrlsLimit: ", this->topUrlsLimit);
        Debug::print("----> topRefsLimit: ", this->topRefsLimit);
    }
}

void Config::help() {
    std::cout << std::endl;
    std::cout << "Program" << std::endl;
    std::cout << std::endl;
    std::cout << "  HTTP logs analyzer" << std::endl;
    std::cout << std::endl;
    std::cout << "Params" << std::endl;
    std::cout << std::endl;
    std::cout << "  -f — Log file. Example: ./http-logs-analyzer -f example/access_log" << std::endl;
    std::cout << "  -d — Debug mode. Example: ./http-logs-analyzer -f example/access_log -d" << std::endl;
    std::cout << "  -i — IP pattern. Example: ./http-logs-analyzer -f example/access_log -i \"^([0-9]+\\.[0-9]+\\.[0-9]+\\.[0-9]+)\"" << std::endl;
    std::cout << "  -a — UserAgent pattern. Example: ./http-logs-analyzer -f example/access_log -a \"\\\" \\\"([^\\\"]+)\\\"\"" << std::endl;
    std::cout << "  -u — URL pattern. Example: ./http-logs-analyzer -f example/access_log -u \"\\\"[a-zA-Z]+T (/[^\\\"]+) HTTP\"" << std::endl;
    std::cout << "  -r — Referer pattern. Example: ./http-logs-analyzer -f example/access_log -r \"\\\"[^\\\"]+\\\"([^\\\"]+)\\\" \\\"\"" << std::endl;
    std::cout << "  -t — Traffic pattern. Example: ./http-logs-analyzer -f example/access_log -t \"HTTP/[0-9]\\\\.[0-9]\\\" [0-9][0-9][0-9]? ([0-9]+)[0-9 ]*\\\"\"" << std::endl;
}

