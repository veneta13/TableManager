#include "../inc/validator.h"

/**
 * @brief validate command name
 * 
 * @param name command name
 */
void Validator::validateName(std::string& name) {
    for (int i = 0; i < 10; i++) {
        if (validCommandNames[i] == name) {return;}
    }
    throw std::invalid_argument("Error: Invalid command name.");
}

/**
 * @brief validate command arguments
 * 
 * @param name - command name
 * @param args command arguments
 */
void Validator::validateArgs(std::string name, vector<string>& args) {
    if (name == "PRINT VAL ALL" || name == "PRINT EXPR ALL" || name == "EXIT") {
        if (args.size() != 0) {
            throw std::invalid_argument("Error: This command requires no arguments.");
        }
    }
    else if (name == "PRINT VAL" || name == "PRINT EXPR" || name == "SAVE" || 
             name == "LOAD" || name == "++" || name == "--") {
        if (args.size() != 1) {
            throw std::invalid_argument("Error: This command requires one argument.");
            }
    }
    else if (name == "SET")  {
        if (args.size() != 2) {
            throw std::invalid_argument("Error: This command two arguments.");
            } 
    }
}
