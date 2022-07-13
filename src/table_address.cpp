#include "../inc/table_address.h"


/// Default constructor
Address::Address() = default;


/// Constructor with parameters
/// \param _row row index
/// \param _column column index
Address::Address(int _row, int _column) : row(_row), column(_column) {}


/// Constructor with parameters
/// \param text text to read address from
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


/// Constructor with parameters
/// \param text text to read address from
/// \param currentRow current row (in case of relative indexing)
/// \param currentColumn current column (in case of relative indexing)
Address :: Address (const char *& text, int currentRow, int currentColumn) {
    if (*text == 'R') {
        readAddress(text, currentRow, row);
    }
    else {
        throw std::runtime_error("Invalid row address");
    }

    if (*text == 'C') {
        readAddress(text, currentColumn, column);
    }
    else {throw std::runtime_error("Invalid column address");}
}


/// Compare addresses with equality operator
/// \param other address to compare to
/// \return if the addresses are equal
bool Address :: operator==(Address const& other) const {
    return column == other.column && row == other.row;
}


/// Get integer value of text
/// \param text text to read number from
/// \return integer value of the text
int Address :: getNumber (const char *& text) {
    int number = 0;
    while (std::isdigit(*text)) {
        number *= 10;
        number += (*text - '0');
        text++;
    }
    return number;
}


/// Extract address from text
/// \param text text to extract address from
/// \param current currently opened cell address
/// \param updated new cell address
void Address::readAddress(char const*& text, int& current, int& updated) {
    text++;

    if (*text == '['){
        text++;

        if (*text == '-') {
            text++;
            updated = current - getNumber(text);
        }
        else {
            updated = current + getNumber(text);
        }

        if (*text == ']') {
            text++;
        }
        else {
            throw std::runtime_error("Error: wrong relative addressing!");
        }
    }
    else {
        updated = getNumber(text);
    }
}
