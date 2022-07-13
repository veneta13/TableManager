#include "command.h"


/// Default constructor
Command::Command() = default;


/// Copy constructor
/// \param other command to copy
Command::Command(Command& other) {
    setName(other.getName());
    setArguments(other.getArguments());
}


/// Copy assignment operator
/// \param other command to copy
/// \return updated command
Command& Command::operator=(Command other) {
    if (this != &other) {
        setName(other.getName());
        setArguments(other.getArguments());
    }
    return *this;
}


/// Destructor
Command::~Command() = default;


/// Command name getter
/// \return the name of the command
string Command::getName() const {
    return name;
}


/// Command name setter
/// \param newName updated name of the command
void Command::setName(string const& newName) {
    Validator::instance()->validateName(newName);
    name = newName;
}


/// Command arguments getter
/// \return the arguments of the command
vector<string>& Command::getArguments() {
    return args;
}


/// Command arguments setter
/// \param args updated arguments of the command
void Command::setArguments(vector<string>& newArguments) {
    args = newArguments;
    Validator::instance()->validateArgs(name, args);
}


/// Count number of arguments of the command
/// \return the number of arguments of the command
int Command::argumentCount() const {
    return (int)args.size();
}
