#ifndef STACK_TABLE_HASH_H
#define STACK_TABLE_HASH_H

#include "table_address.h"

#include <string>

using std::string;

/// Represents the table hash function
struct TableHash {
    TableHash();
    TableHash(TableHash const& other) = delete;
    TableHash& operator=(TableHash const& other) = delete;
    ~TableHash();

    size_t operator() (Address const& address) const;
};

#endif //STACK_TABLE_HASH_H
