#include "../inc/table.h"

/**
 * @brief constructor 
 * 
 * @return Table with default max adress(0, 0)
 */
Table :: Table() {
    currentMaxAddress = Address{0, 0};
}

/**
 * @brief hash function
 * 
 * @param address the adress to be hashed
 * @return size_t the hash of the address
 */
size_t TableHash :: operator() (Address const& address) const{
    std::hash<string> hashFunc;
    string hashString = "";
    hashString += std::to_string(address.column) + "col";
    hashString += std::to_string(address.row) + "row";
    return hashFunc(hashString);
}

/**
 * @brief Set the Cell object
 * 
 * @param address the address of the cell
 * @param value the expression value to be given to the cell
 */
void Table :: setCell(Address address, std::string value) {
    tableMap[address] = value;
    if (address.row > currentMaxAddress.row) {
        currentMaxAddress.row = address.row;
    }
    if (address.column > currentMaxAddress.column) {
        currentMaxAddress.column = address.column;
    }
}

/**
 * @brief Get the cell expression
 * 
 * @param address the address of the cell
 * @return std::string the expression saved in the cell
 */
std::string Table :: getCell(Address address) const {
    if (tableMap.find(address) == tableMap.end()) {
        return "";
    }
    return tableMap.at(address);
}

/**
 * @brief Get the value of the cell
 * 
 * @param address the address of the cell
 * @return int the calculated value of the cell
 */
int Table :: getCellValue(Address address) const {
    if (tableMap.find(address) == tableMap.end()) {
        return 0;
    }
    string value = tableMap.at(address);
    if (value == "") {return 0;}
    if (value[0] == '\"') {
        try {
            return std::stoi(value);
        }
        catch(...) {
            return 0;
        }
    }
    else {
        return shuntingYard(value.c_str());
    }
}

/**
 * @brief Get the Max Address object
 * 
 * @return Address the address of the the max cell of the table
 */
Address Table :: getMaxAddress() const {
    return currentMaxAddress;
}

/**
 * @brief Set the Current Address
 * 
 * @param address the new current address
 */
void Table :: setCurrentAddress(Address address) {
    currentAddress = address;
}

/**
 * @brief Get the Current Address
 * 
 * @return Address the current address
 */
Address Table :: getCurrentAddress() const {
    return currentAddress;
}
