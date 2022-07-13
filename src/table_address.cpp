#include "../inc/table_address.h"

/**
 * @brief compare two addresses
 * 
 * @param a another address
 * @return true the addresses are equal
 * @return false the addresses are not equal
 */
bool Address :: operator==(const Address &a) const {
    return column == a.column && row == a.row;
}

/**
 * @brief constructor
 * 
 * @param text the value of the cell
 * @param currentRow current row (in case of relative indexing)
 * @param currentColumn current column (in case of relative indexing)
 * @return Address 
 */
Address :: Address (const char *& text, int currentRow, int currentColumn) {
    if (*text == 'R') {
        text++;
        if (*text == '['){
            text++;
            if (*text == '-') {
                text++;
                row = currentRow - getNumber(text);
            }
            else {
                row = currentRow + getNumber(text);
            }
            if (*text == ']') {
                text++;
            }
            else {
                throw std::runtime_error("Error: wrong relative addressing!");
            }
        }
        else {
            row = getNumber(text);
        }
    }
    else {throw std::runtime_error("Invalid row address");}
    if (*text == 'C') {
        text++;
        if (*text == '['){
            text++;
            if (*text == '-') {
                text++;
                column = currentColumn - getNumber(text);
            }
            else {
                column = currentColumn + getNumber(text);
            }
            if (*text == ']') {
                text++;
            }
            else {
                throw std::runtime_error("Error: wrong relative addressing!");
            }
        }
        else {
            column = getNumber(text);
        }
    }
    else {throw std::runtime_error("Invalid column address");}
}

/**
 * @brief constructor
 * 
 * @param text the value of the cell
 * @return Address the address of the cell
 */
Address :: Address (const char *& text) {
    if (*text == 'R') {
        text++;
        row = getNumber(text);
    }
    else {throw std::runtime_error("Invalid row address");}

    if (*text == 'C') {
        text++;
        column = getNumber(text);
    }
    else {throw std::runtime_error("Invalid column address");}
}

/**
 * @brief get integer value of string 
 * 
 * @param text the text
 * @return int the value
 */
int Address :: getNumber (const char *& text) {
    int number = 0;
    while (std::isdigit(*text)) {
        number *= 10;
        number += (*text - '0');
        text++;
    }
    return number;
}
