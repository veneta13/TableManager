#ifndef VALIDATOR
#define VALIDATOR

#include <vector>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;

/**
 * @brief validates commands
 * 
 */
class Validator{
    string validCommandNames[10] ={"SET", 
                                  "PRINT VAL",
                                  "PRINT EXPR",
                                  "SAVE",
                                  "PRINT EXPR ALL",
                                  "PRINT VAL ALL",
                                  "LOAD",
                                  "++",
                                  "--",
                                  "EXIT"};

    Validator() = default;
    Validator(const Validator&) = delete;
    Validator& operator= (const Validator&) = delete;

public:
    static Validator* instance() {
        static Validator i;
        return &i;
    }
    
    void validateName(std::string& name);
    void validateArgs(std::string name, std::vector <std::string>& args);
};

#endif 