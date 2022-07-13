#ifndef __EXPRESSIONHANDLER_H__
#define __EXPRESSIONHANDLER_H__

#include "tableAddress.h"
#include "table.h"
#include "myOperator.h"

#include <stack>
#include <stdexcept>
#include <cassert>

using std::stack;

class ExpressionHandler {
    int readNumber (const char *& expr) const;
    void calculate(stack<int>& numberStack, const MyOperator* currentOperator) const;
    vector<Address> getTableBoundAddresses(const char *&  expr) const;

    void sumShuntingYard(stack<int>& numberStack, const char* expr) const;
    void countShuntingYard(stack<int>& numberStack, char const* expr) const;

public:
    int shuntingYard(const char* expr) const;

    void notShuntingYard(stack<MyOperator const *> &operatorStack) const;

    void orShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack) const;

    void andShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack) const;

    void ifShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack, char const *expr) const;
};


#endif
