#ifndef __MYOPERATOR_H__
#define __MYOPERATOR_H__

#include <stdexcept>
#include <vector>

using std::vector;

/// Operator interface
struct MyOperator {
    char symbol; // the symbol of the operator
    int priority; // the priority of the operator

    MyOperator();
    MyOperator(char _symbol, int _priority);
    MyOperator(MyOperator const& other);
    MyOperator& operator=(MyOperator const& other);
    
    virtual int calculate(int left, int right) const = 0;
    virtual ~MyOperator();
};

#endif // __MYOPERATOR_H__
