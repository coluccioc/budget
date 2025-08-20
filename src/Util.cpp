#include "Util.hpp"

void Util::runScript(const std::string& scriptPath)
{
    system(scriptPath.c_str());
}

std::string Util::trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) return ""; // All whitespace
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}