#ifndef REGEX_H
#define	REGEX_H

#include <regex.h>
#include "Config.h"
#include "Debug.h"
#include "Patterns.h"

/* Text versions of regexps */
typedef struct {
    std::string ip;
    std::string agent;
    std::string url;
    std::string traffic;
} LogRegexTexts;

/* Compiled regexps */
typedef struct {
    regex_t ip;
    regex_t agent;
    regex_t url;
    regex_t traffic;
} LogRegexCompiled;

/*
 * Text regexps representations 
 * for different log line parts.
 */
static void logRegexTextsFill(LogRegexTexts *lrt) {
    (*lrt).ip = IP_PATTERN;
    (*lrt).agent = AGENT_PATTERN;
    (*lrt).url = URL_PATTERN;
    (*lrt).traffic = TRAFFIC_PATTERN;
}

/*
 * Compiled representations
 * of text regexps.
 */
static void logRegexForCompileFill(LogRegexCompiled *lrc) {
    regex_t ipRegex;
    regex_t agentRegex;
    regex_t urlRegex;
    regex_t trafficRegex;
    (*lrc).ip = ipRegex;
    (*lrc).agent = agentRegex;
    (*lrc).url = urlRegex;
    (*lrc).traffic = trafficRegex;
    regfree(&ipRegex);
    regfree(&agentRegex);
    regfree(&urlRegex);
    regfree(&trafficRegex);
}

/*
 * Compiles text regexp to regex_t.  
 */
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

/*
 * Compiles all texts regexps into regex_t. 
 */
static LogRegexCompiled logRegexCompileAll(const LogRegexTexts * regexps, LogRegexCompiled *lrComp, Config * config) {
    compileRegex(&(*lrComp).ip, (*regexps).ip.c_str(), config);
    compileRegex(&(*lrComp).agent, (*regexps).agent.c_str(), config);
    compileRegex(&(*lrComp).url, (*regexps).url.c_str(), config);
    compileRegex(&(*lrComp).traffic, (*regexps).traffic.c_str(), config);
}

/*
 * Compares text with regexp. 
 */
static std::string matchRegex(regex_t * r, const char * to_match, Config * config) {
    const char * p = to_match;
    regmatch_t m[2]; // matches found 0 - whole match, 1 - submatch
    int nomatch = regexec(r, p, 2, m, 0);
    if (nomatch) {
        if (config->debugMode) {
            Debug::print("matchRegex: No matches");
        }
        return "";
    }
    int start;
    int finish;
    if (m[1].rm_so == -1) {
        if (config->debugMode) {
            Debug::print("matchRegex: error, matched.rm_so == -1");
        }
        return "";
    }
    start = m[1].rm_so + (p - to_match);
    finish = m[1].rm_eo + (p - to_match);
    char buffer[50]; 
    sprintf(buffer, "'%.*s' ", (finish - start), (to_match + start));
    std::string result(buffer);
    if (config->debugMode) {
        Debug::print("matchRegex: found " + result);
    }
    return result;
}

#endif	/* REGEX_H */

