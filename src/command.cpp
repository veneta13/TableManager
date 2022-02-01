#include "../inc/command.h"

/**
 * @brief get command name
 * 
 * @return string command name
 */
string Command::getName() {
    return name;
}

/**
 * @brief get command arguments
 * 
 * @return vector<string>& command arguments
 */
vector<string>& Command::getArguments() {
    return args;
}

/**
 * @brief set the name of the command
 * 
 * @param name command name
 */
void Command::setName(string name) {
    Validator::instance()->validateName(name);
    this->name = name;
}

/**
 * @brief set the arguments of the command
 * 
 * @param args command arguments
 */
void Command::setArguments(vector<string> args) {
    this->args = args;
    Validator::instance()->validateArgs(name, args);
}

/**
 * @brief get the number of arguments of the command
 * 
 * @return int count
 */
int Command::argumentCount() const {
    return args.size();
}
