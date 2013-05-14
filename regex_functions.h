#ifndef REGEX_H
#define	REGEX_H

#include <regex.h>

static int compileRegex(regex_t * regex, const char * regexText) {
    int error = regcomp (regex, regexText, REG_EXTENDED|REG_NEWLINE);
    if (error != 0) {
        Debug::print("Regex error compiling");
        return 1;
    }
    return 0;
}

static std::string matchRegex(regex_t * r, const char * to_match) {
    const char * p = to_match;
    regmatch_t m[1]; // matches found
    int nomatch = regexec(r, p, 1, m, 0);
    if (nomatch) {
        Debug::print("No matches");
        return "";
    }
    int start;
    int finish;
    if (m[0].rm_so == -1) {
        Debug::print("Error: matched.rm_so == -1");
        return "";
    }
    start = m[0].rm_so + (p - to_match);
    finish = m[0].rm_eo + (p - to_match);
    char buffer[50]; 
    sprintf(buffer, "'%.*s' ", (finish - start), (to_match + start));
    std::string result(buffer);
    Debug::print("Found: " + result);
    return result;
}

#endif	/* REGEX_H */

