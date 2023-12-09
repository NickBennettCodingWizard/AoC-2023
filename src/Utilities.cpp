#include "Utilities.ipp"

#include "InputDirectoryConfig.hpp"
#include <fstream>
#include <iostream>

std::string util::GetInputFile(const std::string& x)
{
    return config::GetInputFilePath() + "/" + x;
}

std::vector<std::string> util::Parse(const std::string& x)
{
    std::vector<std::string> contents;

    std::ifstream ifs(x);
    if(ifs.is_open())
    {
        for(std::string line; std::getline(ifs, line);)
        {
            contents.push_back(line);
        }

        // Add the trailing new line to preserve input representation.
        contents.emplace_back();
    }
    else
    {
        std::cerr << "Could not open '" << x << "'\n";
    }

    return contents;
}

std::vector<std::string> util::Split(const std::string& x, char delimiter)
{
    std::vector<std::string> tokens;

    std::stringstream ss(x);
    std::string s;
    while(std::getline(ss, s, delimiter))
    {
        tokens.push_back(s);
    }

    return tokens;
}
