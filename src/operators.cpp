#include "../inc/operators.h"

// Default constructor
Addition::Addition() : MyOperator('+', 5) {}


// Destructor
Addition::~Addition() = default;


/// Calculate + expression
/// \param right right argument
/// \param left left argument
/// \return the sum of the arguments
int Addition::calculate(int right, int left) const  {
    return left + right;
}

// Default constructor
Subtraction::Subtraction() : MyOperator('-', 5) {}


// Destructor
Subtraction::~Subtraction() = default;


/// Calculate - expression
/// \param right right argument
/// \param left left argument
/// \return the difference of the arguments
int Subtraction::calculate(int right, int left) const  {
    return left - right;
}


// Default constructor
Multiplication::Multiplication() : MyOperator('*', 10) {}


// Destructor
Multiplication::~Multiplication() = default;


/// Calculate * expression
/// \param right right argument
/// \param left left argument
/// \return the product of the arguments
int Multiplication::calculate(int right, int left) const  {
    return left * right;
}


// Default constructor
Division::Division() : MyOperator('/', 10) {}


// Destructor
Division::~Division() = default;


/// Calculate / expression
/// \param right right argument
/// \param left left argument
/// \return the quotient of the arguments
int Division::calculate(int right, int left) const  {
    return left / right;
}


// Default constructor
BracketOpen::BracketOpen() : MyOperator('(', 2) {}


// Destructor
BracketOpen::~BracketOpen() = default;


/// Calculate ( expression
/// \param right right argument
/// \param left left argument
/// \return throws runtime error
int BracketOpen::calculate(int right, int left) const  {
    throw std::runtime_error("Error: trying to calculate (!");
}


// Default constructor
BracketClose::BracketClose() : MyOperator(')', 50) {}


// Destructor
BracketClose::~BracketClose() = default;


/// Calculate ) expression
/// \param right right argument
/// \param left left argument
/// \return throws runtime error
int BracketClose::calculate(int right, int left) const  {
    throw std::runtime_error("Error: trying to calculate )!");
}


// Default constructor
LessThan::LessThan() : MyOperator('<', 0) {}


// Destructor
LessThan::~LessThan() = default;


/// Calculate < expression
/// \param right right argument
/// \param left left argument
/// \return if left is less than right
int LessThan::calculate(int right, int left) const  {
    return left < right;
}


// Default constructor
GreaterThan::GreaterThan() : MyOperator('>', 0) {}


// Destructor
GreaterThan::~GreaterThan() = default;


/// Calculate > expression
/// \param right right argument
/// \param left left argument
/// \return if left is greater than right
int GreaterThan::calculate(int right, int left) const  {
    return left > right;
}


// Default constructor
NotEqual::NotEqual() : MyOperator('!', 0) {}


// Destructor
NotEqual::~NotEqual() = default;


/// Calculate != expression
/// \param right right argument
/// \param left left argument
/// \return if left is not equal to right
int NotEqual::calculate(int right, int left) const  {
    return left != right;
}


// Default constructor
Equal::Equal() : MyOperator('=', 0) {}


// Destructor
Equal::~Equal() = default;


/// Calculate == expression
/// \param right right argument
/// \param left left argument
/// \return if left is equal to right
int Equal::calculate(int right, int left) const  {
    return left == right;
}


// Default constructor
And::And() : MyOperator('&', 1) {}


// Destructor
And::~And() = default;


/// Calculate && expression
/// \param right right argument
/// \param left left argument
/// \return if left and right
int And::calculate(int right, int left) const  {
    return left && right;
}


// Default constructor
Or::Or() : MyOperator('|', 1) {}


// Destructor
Or::~Or() = default;


/// Calculate || expression
/// \param right right argument
/// \param left left argument
/// \return if left or right
int Or::calculate(int right, int left) const  {
    return left || right;
}


// Default constructor
Not::Not() : MyOperator('~', 100) {}


// Destructor
Not::~Not() = default;


/// Calculate ~ expression
/// \param right right argument
/// \param left left argument
/// \return negated argument
int Not::calculate(int right, int left) const  {
    return right == 0 ? 1 : 0;
}
