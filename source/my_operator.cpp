#include "my_operator.h"

// Default constructor
MyOperator::MyOperator() = default;


/// Constructor with parameters
/// \param _symbol symbol parameter
/// \param _priority priority parameter
MyOperator::MyOperator(char _symbol, int _priority) : symbol(_symbol), priority(_priority) {}


/// Copy constructor
/// \param other object to copy
MyOperator::MyOperator(MyOperator const &other) : symbol(other.symbol), priority(other.priority) {}


/// Copy assignment operator
/// \param other object to copy
/// \return updated object
MyOperator &MyOperator::operator=(MyOperator const &other) {
    if (this != &other) {
        symbol = other.symbol;
        priority = other.priority;
    }
    return *this;
}


/// Destructor
MyOperator::~MyOperator() = default;
