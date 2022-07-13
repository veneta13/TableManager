#ifndef STACK_OPERATOR_PICKER_H
#define STACK_OPERATOR_PICKER_H

#include "operators.h"

/// Available operator manager | Singleton
class OperatorPicker
{
    vector<const MyOperator*> myOperators; // registered operators

    OperatorPicker();

    const MyOperator* findOperator(char s);

public:
    OperatorPicker(const OperatorPicker&) = delete;
    OperatorPicker& operator= (const OperatorPicker&) = delete;

    static OperatorPicker* instance();

    void add(const MyOperator* currentOperator);
    const MyOperator* pick(char s);
};

#endif //STACK_OPERATOR_PICKER_H
