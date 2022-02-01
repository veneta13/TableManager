#include "../inc/executorHelperFunctions.h"

/**
 * @brief print expression in cell
 * 
 * @param address the address of the cell
 */
void printExpression(Address address) {
    string value = Table::instance()->getCell(address);
    value = (value.length() > 10) ? "LONG CELL" : value;
    std::cout << value;
}

/**
 * @brief print value of cell
 * 
 * @param address the address of the cell
 */
void printValue(Address address) {
    string value = std::to_string(Table::instance()->getCellValue(address));
    value = (value.length() > 10) ? "LONG CELL" : value;
    std::cout << value;
}

/**
 * @brief print the column table header
 * 
 * @param iteration the iteration of the table the header is for
 * @param times times to print the column
 */
void printColumnLine(int iteration, int times) {
    for (int c = 1; c <= times; c++) {
        std::cout << std::setw(12);
        std::cout <<  "C" << c + iteration * 5;
    }
}
