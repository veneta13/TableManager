#ifndef __COMMANDCREATOR_H__
#define __COMMANDCREATOR_H__

#include "command.h"

/// Command generator | Singleton
class CommandCreator {
    CommandCreator();

    void readArguments(vector<string>& arguments);

    void setFunction(Command *command, vector<string> &arguments);
    void printAllFunction(Command *command, vector<string> &arguments);
    void printFunction(Command *command, vector<string> &arguments);
    void saveLoadIncremDecremFunction(Command *command, vector<string> &arguments);
    void exitFunction(Command *command, vector<string> &arguments);

public:
    CommandCreator(const CommandCreator&) = delete;
    CommandCreator& operator=(const CommandCreator&) = delete;

    static CommandCreator* instance();

    Command* createCommand();
};

#endif // __COMMANDCREATOR_H__
