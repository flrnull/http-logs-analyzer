#include <memory>
#include "Config.h"
#include "Debug.h"
#include "Result.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include "regex_functions.h"

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
    Parser parser(config.get());
    // Create regex
    LogRegexTexts logRegExpsTexts;
    LogRegexCompiled logRegExpsCompiled;
    logRegexTextsFill(&logRegExpsTexts);
    logRegexForCompileFill(&logRegExpsCompiled);
    compileLogRegex(&logRegExpsTexts, &logRegExpsCompiled, config.get());    
    // Parse file
    while(std::getline(logFile, logLine)) {
        parser.parse(logLine, &logRegExpsCompiled);
    }
    if (config->debugMode) {
        Debug::print("End reading file...");
    }
    // Result
    Result::display();   
    return 0;
}
