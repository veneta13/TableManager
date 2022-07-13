#ifndef __TABLE_H__
#define __TABLE_H__

#include "table_hash.h"
#include "expression_handler.h"

#include <functional>
#include <unordered_map>

/// Represents the table | Singleton
class Table {
    /// Table cells
    std::unordered_map<Address, string, TableHash> tableMap;

    /// Address of the currently selected cell
    Address currentAddress;

    /// Address of the current lower right table corner
    Address currentMaxAddress;

    Table();

public:
    Table(const Table&) = delete;
    Table& operator= (const Table&) = delete;

    static Table* instance();

    void setCell(Address address, std::string value);
    string getCell(Address address) const;
    int getCellValue(Address address) const;
    Address getMaxAddress() const; 
    void setCurrentAddress(Address address);
    Address getCurrentAddress() const;
};

#endif // __TABLE_H__
