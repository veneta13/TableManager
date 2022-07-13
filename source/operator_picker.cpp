#include "../inc/operator_picker.h"


/// Default constructor
OperatorPicker::OperatorPicker() = default;


/// Search for operator in available operators
/// \param s operator to search for
/// \return corresponding MyOperator object
const MyOperator* OperatorPicker::findOperator(char s)  {
    for (const MyOperator* const& current : myOperators) {
        if (current->symbol == s) {return current;}
    }
    return nullptr;
}


/// Instance getter for singleton
/// \return instance of the OperatorPicker class
OperatorPicker *OperatorPicker::instance() {
    static OperatorPicker i;
    return &i;
}


/// Register an operator
/// \param currentOperator operator to register
void OperatorPicker::add(MyOperator const *currentOperator) {
    if (currentOperator && !findOperator(currentOperator->symbol)) {
        myOperators.push_back(currentOperator);
    }
}


/// Pick operator by symbol
/// \param s symbol to pick by
/// \return corresponding MyOperator object
const MyOperator *OperatorPicker::pick(char s) {
    return findOperator(s);
}
