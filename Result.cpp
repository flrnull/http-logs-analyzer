#include "Result.h"
#include <iostream>

unsigned int Result::views = 0;
unsigned int Result::visitors = 0;
unsigned int Result::urls = 0;
unsigned int Result::traffic = 0;
unsigned int Result::lines = 0;
unsigned int Result::fails = 0;

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
    std::cout << "}" << std::endl;
}
