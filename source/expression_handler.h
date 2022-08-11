#ifndef __EXPRESSIONHANDLER_H__
#define __EXPRESSIONHANDLER_H__

#include "table.h"
#include "my_operator.h"
#include "operator_picker.h"

#include <stack>
#include <stdexcept>
#include <cassert>

using std::stack;

/// Shunting-yard algorithm implementation | Singleton
class ExpressionHandler {
    ExpressionHandler();

    int readNumber (const char *& expr) const;
    void calculate(stack<int>& numberStack, const MyOperator* currentOperator) const;
    vector<Address> getTableBoundAddresses(const char *&  expr) const;
    void helperAddressResult(vector<Address> &result, int &pos1, int &pos2, string &expression) const;

    void operatorShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack, char const*& expr) const;
    void openingShuntingYard(stack<MyOperator const *> &operatorStack, char const*& expr) const;
    void closingShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack, char const*& expr) const;
    void addressShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack, char const*& expr) const;
    void sumShuntingYard(stack<int>& numberStack, const char*& expr) const;
    void countShuntingYard(stack<int>& numberStack, char const*& expr) const;
    void notShuntingYard(stack<MyOperator const *> &operatorStack) const;
    void orShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack) const;
    void andShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack) const;
    void ifShuntingYard(stack<MyOperator const *> &operatorStack, stack<int> &numberStack, char const*& expr) const;

public:
    ExpressionHandler(const ExpressionHandler&) = delete;
    ExpressionHandler& operator= (const ExpressionHandler&) = delete;

    static ExpressionHandler* instance();

    int shuntingYard(const char* expr) const;
};


#endif
