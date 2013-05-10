#include "Debug.h"
#include <string>
#include <ctime>
#include <iostream>

void Debug::print(std::string string) {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    std::cout << "[" << 1900 + ltm->tm_year << "." << 1 + ltm->tm_mon << "." << ltm->tm_mday << " " << 1 + ltm->tm_hour << ":" << 1 + ltm->tm_min << ":" << 1 + ltm->tm_sec << "]" << " ";
    std::cout << string << std::endl;
} 
