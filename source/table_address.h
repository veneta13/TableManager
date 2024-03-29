#ifndef __ADDRESS_H__
#define __ADDRESS_H__

#include <cctype>
#include <stdexcept>
#include <string>

/// Represents a table cell address
struct Address {
    /// Row in table
    int row;

    /// Column in table
    int column;

    Address();
    Address(int row, int column);
    Address(const char *& text);
    Address(const char *& text, int currentRow, int currentColumn);

    bool operator==(Address const& other) const;

private:
    int getNumber(const char *& text);
    void readAddress(char const*& text, int& current, int& updated);
};

#endif // __ADDRESS_H__
