#ifndef VALIDATOR
#define VALIDATOR

#include <vector>
#include <string>
#include <stdexcept>

using std::vector;
using std::string;

/// Validates commands | Singleton
class Validator {

    /// List of all valid command names
    string validCommandNames[10] = {"SET",
                                    "PRINT VAL",
                                    "PRINT EXPR",
                                    "SAVE",
                                    "PRINT EXPR ALL",
                                    "PRINT VAL ALL",
                                    "LOAD",
                                    "++",
                                    "--",
                                    "EXIT"};

    Validator();

public:
    Validator(const Validator &) = delete;
    Validator& operator=(const Validator &) = delete;

    static Validator *instance();

    void validateName(string const &name);

    void validateArgs(string const &name, vector<string> &args);
};

#endif 