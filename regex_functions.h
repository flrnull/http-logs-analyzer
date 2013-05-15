#ifndef REGEX_H
#define	REGEX_H

#include <regex.h>
#include "Config.h"

typedef struct {
    std::string ip;
} LogRegexTexts;

typedef struct {
    std::string ip;
} LogRegexCompiled;

static void logRegexTextsFill(LogRegexTexts *lrt) {
    (*lrt).ip = "\\[[0-9]{,3}\\.[[0-9]{,3}\\.[[0-9]{,3}\\]";
}

static LogRegexCompiled compileLogRegex(LogRegexTexts * regexps, regex_t regex, Config * config) {
    LogRegexCompiled lrComp = {};
    lrComp.ip = compileRegex(&regex, regexps.ip.c_str(), config);
    return lrComp;
}

static int compileRegex(regex_t * regex, const char * regexText, Config * config) {
    int error = regcomp (regex, regexText, REG_EXTENDED|REG_NEWLINE);
    if (error != 0) {
        if (config->debugMode) {
            Debug::print("compileRegex: Regex error compiling");
        }
        return 1;
    }
    return 0;
}

static std::string matchRegex(regex_t * r, const char * to_match, Config * config) {
    const char * p = to_match;
    regmatch_t m[1]; // matches found
    int nomatch = regexec(r, p, 1, m, 0);
    if (nomatch) {
        if (config->debugMode) {
            Debug::print("matchRegex: No matches");
        }
        return "";
    }
    int start;
    int finish;
    if (m[0].rm_so == -1) {
        if (config->debugMode) {
            Debug::print("matchRegex: error, matched.rm_so == -1");
        }
        return "";
    }
    start = m[0].rm_so + (p - to_match);
    finish = m[0].rm_eo + (p - to_match);
    char buffer[50]; 
    sprintf(buffer, "'%.*s' ", (finish - start), (to_match + start));
    std::string result(buffer);
    if (config->debugMode) {
        Debug::print("matchRegex: found " + result);
    }
    return result;
}

#endif	/* REGEX_H */

