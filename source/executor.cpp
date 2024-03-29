#include "executor.h"

/// Default constructor
Executor::Executor() = default;


/// Creates and executes a user command
void Executor::execute()
{
    Command* command = CommandCreator::instance()->createCommand();

    if (command->getName() == "SET") {
        set(command->getArguments());
    }
    else if (command->getName() == "SAVE") {
        save(command->getArguments());
    }
    else if (command->getName() == "LOAD"){
        load(command->getArguments());
    }
    else if (command->getName() == "PRINT EXPR ALL"){
        printExprAll();
    }
    else if (command->getName() == "PRINT VAL ALL"){
        printValAll();
    }
    else if (command->getName() == "PRINT VAL"){
        printVal(command->getArguments());
    }
    else if (command->getName() == "PRINT EXPR"){
        printExpr(command->getArguments());
    }
    else if (command->getName() == "++"){
        increase(command->getArguments());
    }
    else if (command->getName() == "--"){
        decrease(command->getArguments());
    }
    else if (command->getName() == "EXIT"){
        exit = true;
    }
    else {
        delete command;
        throw std::runtime_error("Error: An error has occured executing the command.");
    }
    delete command;
}


/// Getter for exit flag
/// \return if the program should be terminated
bool Executor::isExit() const {
    return exit;
}


/// SET command
/// \param args SET command parameters
void Executor::set(vector<string>& args) const {
    const char* add = args[0].c_str();
    Address address = Address(add,
        	                  Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);

    Table::instance()->setCell(address, args[1]);
    Table::instance()->setCurrentAddress(address);

    std::cout << "Set the value of " << args[0] << " to " << args[1] << "\n";
}


/// PRINT VAL command
/// \param args PRINT VAL command parameters
void Executor::printVal(vector<string>& args) const {
    const char* add = args[0].c_str();
    Address address = Address(add,
                              Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);

    Table::instance()->setCurrentAddress(address);

    std::cout << args[0] << " = " << Table::instance()->getCellValue(address) << "\n";
}


/// PRINT EXPR command
/// \param args PRINT EXPR command parameters
void Executor::printExpr(vector<string>& args) const {
    const char* add = args[0].c_str();
    Address address = Address(add,
        	                  Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);

    Table::instance()->setCurrentAddress(address);

    std::cout << args[0] << " = " << Table::instance()->getCell(address) << "\n";
}


/// SAVE command
/// \param args SAVE command parameters
void Executor::save(vector<string>& args) const {

    Table::instance()->setCurrentAddress(Address(0, 0));

    std::ofstream file(args[0]);
    if (!file.is_open()) {
        throw std::invalid_argument("Error: Cannot open file.");
    }

    for (int r = 1; r <= Table::instance()->getMaxAddress().row; r++) {
        std::string line;

        for (int c = 1; c <= Table::instance()->getMaxAddress().column; c++) {
            Address address(r,c);
            line += Table::instance()->getCell(address);
            line += ",";
        }

        line[line.length() - 1] = ';';
        line += "\n";
        file << line;
    }
    std::cout << "File saved!\n";
    file.close();
}


/// LOAD command
/// \param args LOAD command parameters
void Executor::load(vector<string>& args) const {
    Table::instance()->setCurrentAddress(Address(0, 0));
    std::ifstream file(args[0]);

    if (!file.is_open()) {
        throw std::invalid_argument("Error: Cannot open file.");
    }

    string line;
    int position, row = 1;

    while (std::getline(file, line)) {
        int column = 1;

        while ((position = line.find(',')) != std::string::npos ||
                (position = line.find(';')) != std::string::npos) {
            Address address(row, column);

            std::string expr = line.substr(0, position);
            line.erase(0, position+1);
            Table::instance()->setCell(address, expr);

            column++;
        }
        row++;
    }
    std::cout << "File loaded!\n";
    file.close();
}


/// ++ command
/// \param args ++ command arguments
void Executor::increase(vector<string>& args) const {
    int intValue;
    const char* add = args[0].c_str();
    Address address = Address(add,
                              Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);

    incrDecrHelper(address, intValue);
    Table:: instance()->setCell(address, std::to_string(intValue+1));
    Table::instance()->setCurrentAddress(address);
}


/// -- command
/// \param args -- command parameters
void Executor::decrease(vector<string>& args) const {
    int intValue;
    const char* add = args[0].c_str();
    Address address = Address(add,
                                   Table::instance()->getCurrentAddress().row,
                                   Table::instance()->getCurrentAddress().column);

    incrDecrHelper(address, intValue);
    Table:: instance()->setCell(address, std::to_string(intValue-1));
    Table::instance()->setCurrentAddress(address);
}


/// Helper for common method is ++ and -- functions
/// \param address table address
/// \param intValue value of the cell
void Executor::incrDecrHelper(Address& address, int& intValue) const {
    string value = Table:: instance()->getCell(address);

    if (value.empty() || value[0] == '\"') {
        throw std::invalid_argument("Error: Cannot increase cell.");
    }

    bool isNegative = false;
    if (value[0] == '-') {
        isNegative = true;
        value.erase(value.begin() + 0);
    }

    if (value.find_first_not_of("0123456789") != std::string::npos) {
        throw std::invalid_argument("Error: Cannot increase cell.");
    }

    intValue = std::stoi(value);
    if (isNegative) {
        intValue *= (-1);
    }
}


/// PRINT EXPR ALL command
void Executor::printExprAll() const {
    Table::instance()->setCurrentAddress(Address(0, 0));
    Address max = Table::instance()->getMaxAddress();
    int tableCount = max.column / 5 + (max.column % 5 == 0 ? 0 : 1);
    int iterations = max.column;

    for (int i = 0; i < tableCount;  i++) {
        printColumnLine(i, 5);
        for (int r = 1; r <= max.row && iterations > 0; r++) {
            std::cout << std::setw(5) << std::left << ("R" + std::to_string(r));
            for (int c = 1; c <= 5; c++) {
                Address address(r, c + i * 5);
                printCellExpr(address);
            }
            std::cout << "\n";
        }

        iterations -= 5;
        std::cout << "\n";
    }
}


/// PRINT VAL ALL command
void Executor::printValAll() const {
    Address max = Table::instance()->getMaxAddress();
    int tableCount = max.column / 5 + (max.column % 5 == 0 ? 0 : 1);
    int iterations = max.column;

    for (int i = 0; i < tableCount;  i++) {
        printColumnLine(i, 5);
        for (int r = 1; r <= max.row; r++) {
            std::cout << std::setw(5) << std::left << ("R" + std::to_string(r));

            for (int c = 1; c <= 5; c++) {
                Address address(r, c + i*5);
                printCellVal(address);
            }
            std::cout << "\n";
        }

        iterations -= 5;
        std::cout << "\n";
    }
}


/// Print the value of the cell
/// \param address cell address
void Executor::printCellVal(Address& address) const {
    Table::instance()->setCurrentAddress(address);
    std::cout << "|";
    std::cout << std::setw(12);
    printValue(address);
    std::cout << "|";
}


/// Print the expression stored in the cell
/// \param address cell address
void Executor::printCellExpr(Address& address) const {
    std::cout << "|";
    std::cout << std::setw(12);
    printExpression(address);
    std::cout << "|";
}


/// PRINT EXPR command
/// \param address address of the cell to print
void Executor::printExpression(Address& address) const {
    string value = Table::instance()->getCell(address);
    value = (value.length() > 10) ? "LONG CELL" : value;
    std::cout << value;
}


/// PRINT VAL command
/// \param address address of the cell to print
void Executor::printValue(Address& address) const {
    string value = std::to_string(Table::instance()->getCellValue(address));
    value = (value.length() > 10) ? "LONG CELL" : value;
    std::cout << value;
}


/// Print table header
/// \param iteration the iteration of the table the header is for
/// \param times times to print the column
void Executor::printColumnLine(int iteration, int times) const {
    for (int c = 1; c <= times; c++) {
        std::cout << std::setw(14) << std::right << "C" + std::to_string(c + iteration * 5);
    }
    std::cout << "\n";
}


/// Instance getter for singleton
/// \return instance of the Executor class
Executor *Executor::instance() {
    static Executor i;
    return &i;
}
