#pragma once

#include <fstream>
#include <string>

class PassConfig
{
public:
    PassConfig() = default;

    std::string getPass() 
    {
        std::string res;
        ifstream is(PATH_TO_CONFIG);
        is >> res;
        return res;
    }
};