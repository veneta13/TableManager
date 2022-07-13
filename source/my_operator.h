#ifndef __MYOPERATOR_H__
#define __MYOPERATOR_H__

#include <stdexcept>
#include <vector>

using std::vector;

/// Operator interface
struct MyOperator {
    /// Symbol representing the operator
    char symbol;

    /// Priority of the operator
    int priority;

    MyOperator();
    MyOperator(char _symbol, int _priority);
    MyOperator(MyOperator const& other);
    MyOperator& operator=(MyOperator const& other);
    
    virtual int calculate(int left, int right) const = 0;
    virtual ~MyOperator();
};

#endif // __MYOPERATOR_H__
