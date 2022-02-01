#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "validator.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

/**
 * @brief console command
 * 
 */
struct Command {
    Command() = default;
    ~Command() = default;
    string getName();
    void setName(string name);
    vector<string>& getArguments();
    void setArguments(vector<string> args);
    int argumentCount() const;

private:
    std::string name; // the name of the command
    std::vector <std::string> args; // the arguments passed to the command
};

#endif // __COMMAND_H__
