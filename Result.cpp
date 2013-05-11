#include "Result.h"
#include <iostream>

unsigned int Result::views = 0;
unsigned int Result::parseFails = 0;

void Result::display() {
    std::cout << "{" << std::endl;
    std::cout << "  views: " << Result::views << "," << std::endl;
    std::cout << "  parseFails: " << Result::parseFails << "," << std::endl;
    std::cout << "}" << std::endl;
}
