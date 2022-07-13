#ifndef __TABLE_H__
#define __TABLE_H__

#include "table_address.h"
#include "expression_handler.h"

#include <functional>
#include <string>
#include <unordered_map>

using std::string;

/**
 * @brief Table hash class
 * 
 */
class TableHash {
public:
    size_t operator() (Address const& address) const;
};

/**
 * @brief the cell table
 * 
 */
class Table {
    std::unordered_map<Address, string, TableHash> tableMap; //table cells

    Address currentAddress; //address of the currectly selected cell
    Address currentMaxAddress; //address of the current lower right table corner

    Table();
    Table(const Table&) = delete;
    Table& operator= (const Table&) = delete;

public:
    static Table* instance() {
        static Table i;
        return &i;
    }

    void setCell(Address address, std::string value);
    std::string getCell(Address address) const;
    int getCellValue(Address address) const;
    Address getMaxAddress() const; 
    void setCurrentAddress(Address address);
    Address getCurrentAddress() const;
};

#endif // __TABLE_H__
