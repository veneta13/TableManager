#ifndef __TABLE_H__
#define __TABLE_H__

#include "table_hash.h"
#include "expression_handler.h"

#include <functional>
#include <unordered_map>

/// Represents the table | Singleton
class Table {
    std::unordered_map<Address, string, TableHash> tableMap; //table cells

    Address currentAddress; // address of the currently selected cell
    Address currentMaxAddress; // address of the current lower right table corner

    Table();

public:
    Table(const Table&) = delete;
    Table& operator= (const Table&) = delete;

    static Table* instance();

    void setCell(Address address, std::string value);
    std::string getCell(Address address) const;
    int getCellValue(Address address) const;
    Address getMaxAddress() const; 
    void setCurrentAddress(Address address);
    Address getCurrentAddress() const;
};

#endif // __TABLE_H__
