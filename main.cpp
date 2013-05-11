#include <memory>
#include "Config.h"
#include "Debug.h"
#include "Result.h"
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    // Init and validate params
    std::auto_ptr<Config> config(Config::getInstance());
    config->parseArgs(argc, argv);
    config->debug();
    std::ifstream logFile(config->logName.c_str(), std::ifstream::in);
    if (!logFile) {
        Debug::print("Error: file " + config->logName + " is not exists!");
        exit(1);
    }
    // Collect data
    if (config->debugMode) {
        Debug::print("Start reading file...");
    }
    std::string logLine;
    while(std::getline(logFile, logLine)) {
        Result::views++;
    }
    // Result
    Result::display();
    return 0;
}
