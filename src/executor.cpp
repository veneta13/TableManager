#include "../inc/executor.h"

#include <iostream>

/**
 * @brief generate and execute commands
 * 
 */
void Executor::execute()
{
    Command* command = CommandCreator::instance()->createCommand();

    if (command->getName().compare("SET") == 0){
        set(command->getArguments());
    }
    else if (command->getName().compare("SAVE") == 0){
        save(command->getArguments());
    }
    else if (command->getName().compare("LOAD") == 0){
        load(command->getArguments());
    }
    else if (command->getName().compare("PRINT EXPR ALL") == 0){
        printExprAll();
    }
    else if (command->getName().compare("PRINT VAL ALL") == 0){
        printValAll();
    }
    else if (command->getName().compare("PRINT VAL") == 0){
        printVal(command->getArguments());
    }
    else if (command->getName().compare("PRINT EXPR") == 0){
        printExpr(command->getArguments());
    }
    else if (command->getName().compare("++") == 0){
        increase(command->getArguments());
    }
    else if (command->getName().compare("--") == 0){
        decrease(command->getArguments());
    }
    else if (command->getName().compare("EXIT") == 0){
        exit = true;
    }
    else {
        delete command;
        throw std::runtime_error("Error: An error has occured executing the command.");
    }
    delete command;
}

/**
 * @brief check is EXIT flag is up
 * 
 * @return true the program will exit
 * @return false the program won't exit
 */
bool Executor::isExit() {
    return exit;
}

/**
 * @brief execute SET command
 * 
 * @param args command arguments
 */
void Executor::set(vector<string>& args) {
    const char* add = args[0].c_str();
    Address address = Address(add,
        	                  Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);
    Table::instance()->setCell(address, args[1]);
    Table::instance()->setCurrentAddress(address);
    std::cout << "Set the value of " << args[0] << " to " << args[1] << "\n";
}

/**
 * @brief execute PRINT VAL command
 * 
 * @param args command arguments
 */
void Executor::printVal(vector<string>& args) {
    const char* add = args[0].c_str();
    Address address = Address(add,
                              Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);
    Table::instance()->setCurrentAddress(address);
    std::cout << args[0]  
              << " = "
              << Table::instance()->getCellValue(address)
              << "\n";
}

/**
 * @brief execute PRINT EXPR command
 * 
 * @param args command arguments
 */
void Executor::printExpr(vector<string>& args) {
    const char* add = args[0].c_str();
    Address address = Address(add,
        	                  Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);
    Table::instance()->setCurrentAddress(address);
    std::cout << args[0] 
              << " = "
              << Table::instance()->getCell(address)
              << "\n";
}

/**
 * @brief execute SAVE command
 * 
 * @param args command arguments
 */
void Executor::save(vector<string>& args) {
    Table::instance()->setCurrentAddress(Address(0, 0));
    std::ofstream file(args[0]);
    if (file.is_open()) {
        for (int r = 1; r <= Table::instance()->getMaxAddress().row; r++) {
            std::string line = "";

            for (int c = 1; c <= Table::instance()->getMaxAddress().column; c++) {
                Address address(r,c);
                line += Table::instance()->getCell(address);
                line += ",";
            }

            line[line.length() - 1] = ';';
            line += "\n";
            file << line;
        }
        file.close();
    }
    else {
        throw std::invalid_argument("Error: Cannot open file.");
    }
}

/**
 * @brief execute LOAD command
 * 
 * @param args command arguments
 */
void Executor::load(vector<string>& args) {
    Table::instance()->setCurrentAddress(Address(0, 0));
    std::ifstream file(args[0]);
    if (file.is_open()) {
        string line;
        int p, r = 1;
        while (std::getline(file, line))
        {
            int c = 1;
            while ((p = line.find(",")) != std::string::npos || (p = line.find(";")) != std::string::npos) {
                Address address(r, c);
                std::string expr = line.substr(0, p);
                line.erase(0, p+1);
                Table::instance()->setCell(address, expr);
                c++;
            }
            r++;
        }
        file.close();
    }
    else {
        throw std::invalid_argument("Error: Cannot open file.");
    }
}

/**
 * @brief execute ++ command
 * 
 * @param args command arguments
 */
void Executor::increase(vector<string>& args) {
    const char* add = args[0].c_str();
    Address address = Address(add,
        	                  Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);
    string value = Table:: instance()->getCell(address);

    if (value == "" || value[0] == '\"') {
        throw std::invalid_argument("Error: Cannot increase cell.");
    }

    bool isNegative = false;
    if (value[0] == '-') {
        isNegative = true;
        value.erase(value.begin() + 0);
    }
    if (value.find_first_not_of("0123456789") == std::string::npos) {
        int i = std::stoi(value);
        if (isNegative) {i *= (-1);}
        Table:: instance()->setCell(address, std::to_string(i+1));
    }
    else {
        throw std::invalid_argument("Error: Cannot increase cell.");
    }
    Table::instance()->setCurrentAddress(address);
}

/**
 * @brief execute -- command
 * 
 * @param args command arguments
 */
void Executor::decrease(vector<string>& args) {
    const char* add = args[0].c_str();
    Address address = Address(add,
        	                  Table::instance()->getCurrentAddress().row,
                              Table::instance()->getCurrentAddress().column);
    string value = Table:: instance()->getCell(address);

    if (value == "" || value[0] == '\"') {
        throw std::invalid_argument("Error: Cannot increase cell.");
    }

    bool isNegative = false;
    if (value[0] == '-') {
        isNegative = true;
        value.erase(value.begin() + 0);
    }
    if (value.find_first_not_of("0123456789") == std::string::npos) {
        int i = std::stoi(value);
        if (isNegative) {i *= (-1);}
        Table:: instance()->setCell(address, std::to_string(i-1));
    }
    else {
       throw std::invalid_argument("Error: Cannot increase cell.");
    }
    Table::instance()->setCurrentAddress(address);
}

/**
 * @brief execute PRINT EXPR ALL command
 * 
 */
void Executor::printExprAll() {
    Table::instance()->setCurrentAddress(Address(0, 0));
    Address max = Table::instance()->getMaxAddress();
    int iterations = max.column / 5;
    int lastIteration = max.column % 5;

    for (int i = 0; i < iterations;  i++) {
        printColumnLine(i, 5);
        std::cout << "\n";
        for (int r = 1; r <= max.row; r++) {
            std::cout << "R" << r;
            for (int c = 1; c <= 5; c++) {
                Address address(r, c + i*5);
                std::cout << "|";
                std::cout << std::setw(12);
                printExpression(address);
                std::cout << "|";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    printColumnLine(iterations, lastIteration);
    std::cout << "\n";
    for (int r = 1; r <= max.row; r++) {
        std::cout << "R" << r;
        for (int c = 1; c <= lastIteration; c++) {
            Address address(r, c+iterations*5);
            std::cout << "|";
            std::cout << std::setw(12);
            printExpression(address);
            std::cout << "|";
        }
        std::cout << "\n";
    }
}

/**
 * @brief execute PRINT VAL ALL command
 * 
 */
void Executor::printValAll() {
    Address max = Table::instance()->getMaxAddress();
    int iterations = max.column / 5;
    int lastIteration = max.column % 5;

    for (int i = 0; i < iterations;  i++) {
        printColumnLine(i, 5);
        std::cout << "\n";
        for (int r = 1; r <= max.row; r++) {
            std::cout << "R" << r;
            for (int c = 1; c <= 5; c++) {
                Address address(r, c + i*5);
                Table::instance()->setCurrentAddress(address);
                std::cout << "|";
                std::cout << std::setw(12);
                printValue(address);
                std::cout << "|";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    printColumnLine(iterations, lastIteration);
    std::cout << "\n";
    for (int r = 1; r <= max.row; r++) {
        std::cout << "R" << r;
        for (int c = 1; c <= lastIteration; c++) {
            Address address(r, c+iterations*5);
            Table::instance()->setCurrentAddress(address);
            std::cout << "|";
            std::cout << std::setw(12);
            printValue(address);
            std::cout << "|";
        }
        std::cout << "\n";
    }
}


/**
 * @brief print expression in cell
 *
 * @param address the address of the cell
 */
void Executor::printExpression(Address address) {
    string value = Table::instance()->getCell(address);
    value = (value.length() > 10) ? "LONG CELL" : value;
    std::cout << value;
}

/**
 * @brief print value of cell
 *
 * @param address the address of the cell
 */
void Executor::printValue(Address address) {
    string value = std::to_string(Table::instance()->getCellValue(address));
    value = (value.length() > 10) ? "LONG CELL" : value;
    std::cout << value;
}

/**
 * @brief print the column table header
 *
 * @param iteration the iteration of the table the header is for
 * @param times times to print the column
 */
void Executor::printColumnLine(int iteration, int times) {
    for (int c = 1; c <= times; c++) {
        std::cout << std::setw(12);
        std::cout <<  "C" << c + iteration * 5;
    }
}
