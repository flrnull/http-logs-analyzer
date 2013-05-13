#ifndef CONFIG_H
#define	CONFIG_H

#include <string>

class Config
{
private:
    static Config * _instance;
    Config();
    Config(const Config&);
    Config& operator=(Config&);

public:
    ~Config();
    static Config * getInstance();
    void parseArgs(int argc, char **argv);
    void debug();

    // Options
    std::string logName;
    int debugMode;
};

#endif	/* CONFIG_H */

