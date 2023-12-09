#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace util
{
    std::string GetInputFile(const std::string& x);

    std::vector<std::string> Parse(const std::string& x);

    template <class T> T StringTo(const std::string& x)
    {
        T result;
        std::stringstream ss(x);
        ss >> result;

        return result;
    }

    template <class T>
    std::vector<T> ContainerTo(const std::vector<std::string>& x)
    {
        std::vector<T> converted;
        for(const auto& item : x)
        {
            converted.push_back(StringTo<T>(item));
        }

        return converted;
    }

    std::vector<std::string> Split(const std::string& x, char delimiter = ' ');
}
