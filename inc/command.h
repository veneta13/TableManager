#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "validator.h"

#include <iostream>

/// Represents a console command
struct Command {
    Command();
    Command(Command& other);
    Command& operator=(Command other);
    ~Command();

    string getName() const;
    void setName(string const& newName);

    vector<string>& getArguments();
    void setArguments(vector<string>& newArguments);

    int argumentCount() const;

private:
    string name; // name of the command
    vector<string> args; // arguments passed to the command
};

#endif // __COMMAND_H__
