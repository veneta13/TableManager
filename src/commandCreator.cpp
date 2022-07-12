#include "../inc/commandCreator.h"


/// Default constructor
CommandCreator::CommandCreator() = default;


/// Instance getter for singleton
/// \return instance of the CommandCreator class
CommandCreator *CommandCreator::instance() {
    static CommandCreator i;
    return &i;
}


/// Read command from terminal
/// \param arguments parsed terminal input
void CommandCreator::readArguments(vector<string>& arguments) {
    string inputLine;
    string word;

    std::cin.sync();
    std::getline(std::cin, inputLine);
    bool isLeadingSpace = true;

    for (int i = 0; i < inputLine.size(); i++) {
        if (inputLine[i] == ' ') {
            if (isLeadingSpace) { continue; }
            if (!word.empty()) {
                arguments.push_back(word);
                word = "";
            }
        }
        else {
            isLeadingSpace = false;
            word += inputLine[i];
            if (i == inputLine.size() - 1) {
                arguments.push_back(word);
                word = "";
            }
        }
    }
}


/// Updater for SET command
/// \param command command to update
/// \param arguments arguments to update
void CommandCreator::setFunction(Command* command, vector<string>& arguments) {
    command->setName(arguments[0]);
    arguments.erase(arguments.begin() + 0);

    string expression;
    while (arguments.size() != 1) {
        expression += arguments[1] + " ";
        arguments.erase(arguments.begin() + 1);
    }
    expression.pop_back();
    arguments.push_back(expression);
}


/// Updater for PRINT ALL command
/// \param command command to update
/// \param arguments arguments to update
void CommandCreator::printAllFunction(Command* command, vector<string>& arguments) {
    command->setName(arguments[0] + " " + arguments[1] + " " + arguments[2]);
    arguments.erase(arguments.begin() + 2);
    arguments.erase(arguments.begin() + 1);
    arguments.erase(arguments.begin() + 0);
    if (!arguments.empty()) {
        throw std::invalid_argument("Error: Command accepts no arguments.");
    }
}


/// Updater for PRINT command
/// \param command command to update
/// \param arguments arguments to update
void CommandCreator::printFunction(Command* command, vector<string>& arguments) {
    command->setName(arguments[0] + " " + arguments[1]);
    arguments.erase(arguments.begin() + 1);
    arguments.erase(arguments.begin() + 0);

    string expression;
    while (!arguments.empty()) {
        expression += arguments[0] + " ";
        arguments.erase(arguments.begin() + 0);
    }
    expression.pop_back();
    arguments.push_back(expression);
}


/// Updater for SAVE, LOAD, ++ and -- commands
/// \param command command to update
/// \param arguments arguments to update
void CommandCreator::saveLoadIncremDecremFunction(Command* command, vector<string>& arguments) {
    command->setName(arguments[0]);
    arguments.erase(arguments.begin() + 0);

    string expression;
    while (!arguments.empty()) {
        expression += arguments[0] + " ";
        arguments.erase(arguments.begin() + 0);
    }
    expression.pop_back();
    arguments.push_back(expression);
}


/// Updater for EXIT command
/// \param command command to update
/// \param arguments arguments to update
void CommandCreator::exitFunction(Command* command, vector<string>& arguments) {
    command->setName(arguments[0]);
    arguments.erase(arguments.begin() + 0);
    if (!arguments.empty()) {
        throw std::invalid_argument("Error: Command accepts no arguments.");
    }
}


/// Create a new command with user input
/// \return Command object
Command* CommandCreator::createCommand() {
    Command* command = new Command();
    vector<string> arguments;

    readArguments(arguments);

    if (arguments[0] == "SET") {
        setFunction(command, arguments);
    }
    else if (arguments[0] == "PRINT") {
        if (arguments[2] == "ALL") {
            printAllFunction(command, arguments);
        }
        else {
            printFunction(command, arguments);
        }
    }
    else if (arguments[0] == "SAVE" || arguments[0] == "LOAD" || 
             arguments[0] == "++" || arguments[0] == "'--" ) {
        saveLoadIncremDecremFunction(command, arguments);
    }
    else if (arguments[0] == "EXIT") {
        exitFunction(command, arguments);
    }

    command->setArguments(arguments);
    return command;
}
