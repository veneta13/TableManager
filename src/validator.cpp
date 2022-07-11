#include "../inc/validator.h"

/// Default constructor
Validator::Validator() = default;


/// Instance getter for singleton
/// \return instance of the Validator class
Validator *Validator::instance() {
    static Validator i;
    return &i;
}


/// Validate the name of the command
/// \param name the name of the command
void Validator::validateName(std::string const& name) {
    for (int i = 0; i < 10; i++) {
        if (validCommandNames[i] == name) {return;}
    }
    throw std::invalid_argument("Error: Invalid command name.");
}


/// Validate the name and the arguments of the command
/// \param name the name of the command
/// \param args the command arguments
void Validator::validateArgs(std::string const& name, vector<string>& args) {
    if (name == "PRINT VAL ALL" || name == "PRINT EXPR ALL" || name == "EXIT") {
        if (!args.empty()) {
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
