#include "../inc/table_hash.h"


/// Default constructor
TableHash::TableHash() = default;


/// Destructor
TableHash::~TableHash() = default;


/// Address hash function
/// \param address address to hash
/// \return hash of the address
size_t TableHash::operator()(Address const& address) const{
    std::hash<string> hashFunc;
    string hashString;
    hashString = std::to_string(address.column) + "col";
    hashString += std::to_string(address.row) + "row";
    return hashFunc(hashString);
}
