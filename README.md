# Table Management System
### Final project for the DSA course @ FMI.

There is a single table made up of table cells.

Each table cell is either empty or contains text or an expression to calculate its value.

#### Addressing

Cells are addressed by row and column number, with an expression of the type **RxCy** , where x and y specify the row and column of the addressed cell, respectively. 

Cell addressing can be absolute or relative:
- in _absolute_ addressing, rows and columns are counted from the upper left corner of the table;
- with _relative_ addressing, rows and columns are counted from the cell in which the relative addressing expression occurs. Relative addressing is specified when, in an **R[x]C[y]** expression, row or column numbers are enclosed in square brackets.


#### Text cells


Text cells contain arbitrary text enclosed in quotation marks.


#### Expressions


Expressions in cells are arithmetic expressions with **operators** +,-,*,/ and arguments integers or **addresses** of other cells.

The expression in each cell sets its value and is _recalculated_ when any of the cells addressed in it changes its value.

In formulas, you can also use the following functions: **if**, **and**, **not**, **or**, as well as the **Boolean operators** ==, !=, <, > with their natural semantics.

Expressions can be of arbitrary complexity using parentheses and the semantics are as in C++.

_The semantics of **if** are like the ?: operator in C++._


#### Functions


The table must support **sum** and **count** functions with two arguments - cell addresses.

These addresses define the corners of a rectangular area of the table that the functions must operate on. 

The sum function finds the **sum** of the values of those cells, while **count** finds the number of _non-empty_ cells. 

_The values of empty cells in this case are assumed to be 0. If the content of a text cell can be interpreted as a number (whole or fractional), then this is its value. Otherwise, the value is 0._


#### Commands


The system must support the following commands entered by the user in interactive mode:



| Command                    | Description                                                                                                                    |
|----------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| SET _address_ _expression_ | changes the value of the cell with the corresponding address                                                                   |
| PRINT VAL _address_        | prints the value of the cell with the corresponding address                                                                    |
| PRINT EXPR _address_       | prints the formula in the cell with the corresponding address                                                                  |
| PRINT VAL ALL              | prints the values of all cells in the table formatted, with cells in a single row printed on a single line on the screen (*)   |
| PRINT EXPR ALL             | prints the formulas of all cells in the table formatted, with cells in a single row printed on a single line on the screen (*) |
| SAVE _file_                | saves the contents of the table (as formulas) to a .csv file                                                                   |
| LOAD _file_                | reads table contents (as formulas) from a .csv file                                                                            |
| ++ _address_               | if the expression at the corresponding address is an integer, increments it by one                                                                                                                               |
| -- _address_               | if the expression at the corresponding address is an integer, decrements it by one                                                                                                                                         |


_(*)If the screen width is not enough for all the cells of the rows, the table is divided into sub-tables and they are printed one by one._
