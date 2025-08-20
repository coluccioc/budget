#include <chrono>  // For time units
#include <sstream>

namespace Util
{
    // Function to run a script file
    void runScript(const std::string& scriptPath);

    // Function to trim whitespace from a string
    std::string trim(const std::string& str);
};