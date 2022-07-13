#ifndef __TABLECELL_H__
#define __TABLECELL_H__

#include <cctype>
#include <stdexcept>
#include <string>

/**
 * @brief adress container
 * 
 */
struct Address{
    int row; //row in table
    int column; //column in table 

    Address() = default;
    Address(int row, int column) : row(row), column(column) {};
    Address (const char *& text);
    Address (const char *& text, int currentRow, int currentColumn);
    bool operator==(const Address &a) const;

private:
    int getNumber(const char *& text);
};

#endif // __TABLECELL_H__
