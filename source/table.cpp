#include "table.h"


/// Default constructor
Table::Table() : currentMaxAddress(Address{0, 0}) {}


/// Instance getter for singleton
/// \return instance of the Table class
Table *Table::instance() {
    static Table i;
    return &i;
}


/// Set cell value
/// \param address address of the cell to set value to
/// \param value value to set
void Table::setCell(Address address, string value) {
    tableMap[address] = value;

    if (address.row > currentMaxAddress.row) {
        currentMaxAddress.row = address.row;
    }
    if (address.column > currentMaxAddress.column) {
        currentMaxAddress.column = address.column;
    }
}


/// Get cell expression
/// \param address address of the cell to get expression of
/// \return expression saved in the cell
std::string Table::getCell(Address address) const {
    if (tableMap.find(address) == tableMap.end()) {
        return "";
    }
    return tableMap.at(address);
}


/// Get cell value
/// \param address address of the cell to get value of
/// \return value of the cell
int Table::getCellValue(Address address) const {
    if (tableMap.find(address) == tableMap.end()) {
        return 0;
    }
    string value = tableMap.at(address);
    if (value.empty()) { return 0; }
    if (value[0] == '\"') {
        try {
            return std::stoi(value);
        }
        catch(...) {
            return 0;
        }
    }
    else {
        return ExpressionHandler::instance()->shuntingYard(value.c_str());
    }
}


/// Getter for max address
/// \return the max address saved in the table
Address Table::getMaxAddress() const {
    return currentMaxAddress;
}


/// Setter for current address
/// \param address address to set current address to
void Table::setCurrentAddress(Address address) {
    currentAddress = address;
}


/// Getter for current address
/// \return the currently opened address
Address Table::getCurrentAddress() const {
    return currentAddress;
}
