#include "../inc/commandCreator.h"

/**
 * @brief Create a Command object
 * 
 * @return Command* new command
 */
Command* CommandCreator :: createCommand() {
    Command* command = new Command();

    string inputLine;
    string word = "";
    vector<string> arguments;
    
    std::cin.sync();
    std::getline(std::cin, inputLine); 
    bool isLeadingSpace = true;

    for (int i = 0; i < inputLine.size(); i++) {
        if (inputLine[i] == ' ') {
            if (isLeadingSpace) { continue; }
                if (word != "") {
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

    if (arguments[0] == "SET") {
        command->setName(arguments[0]);
        arguments.erase(arguments.begin() + 0);

        string expression = "";
        while (arguments.size() != 1) {
            expression += arguments[1] + " ";
            arguments.erase(arguments.begin() + 1);
        }
        expression.pop_back();
        arguments.push_back(expression);
    }
    else if (arguments[0] == "PRINT") {
        if (arguments[2] == "ALL") {
            command->setName(arguments[0] + " " + arguments[1] + " " + arguments[2]);
            arguments.erase(arguments.begin() + 2);
            arguments.erase(arguments.begin() + 1);
            arguments.erase(arguments.begin() + 0);
            if (arguments.size() != 0) {
                throw std::invalid_argument("Error: Command accepts no argumnets.");
            }
        }
        else {
            command->setName(arguments[0] + " " + arguments[1]);
            arguments.erase(arguments.begin() + 1);
            arguments.erase(arguments.begin() + 0);

            string expression = "";
            while (arguments.size() != 0) {
                expression += arguments[0] + " ";
                arguments.erase(arguments.begin() + 0);
            }
            expression.pop_back();
            arguments.push_back(expression);
        }
    }
    else if (arguments[0] == "SAVE" || arguments[0] == "LOAD" || 
             arguments[0] == "++" || arguments[0] == "'--" ) {
        command->setName(arguments[0]);
        arguments.erase(arguments.begin() + 0);
        
        string expression = "";
        while (arguments.size() != 0) {
            expression += arguments[0] + " ";
            arguments.erase(arguments.begin() + 0);
        }
        expression.pop_back();
        arguments.push_back(expression);
    }
    else if (arguments[0] == "EXIT") {
        command->setName(arguments[0]);
        arguments.erase(arguments.begin() + 0);
        if (arguments.size() != 0) {
            throw std::invalid_argument("Error: Command accepts no argumnets.");
        }
    }

    command->setArguments(arguments);

    return command;
}
