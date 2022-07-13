#ifndef STACK_OPERATOR_SAVER_H
#define STACK_OPERATOR_SAVER_H

#include "operator_picker.h"

/// Operator adder
/// \tparam DT placeholder for operator types
template <typename DT>
class OperatorSaver {
private:
    DT currentOperator; //the operator to be registered

public:
    OperatorSaver() {
        OperatorPicker::instance() -> add(&currentOperator);
    }

    OperatorSaver(OperatorSaver const& other) = delete;
    OperatorSaver& operator=(OperatorSaver const& other) = delete;
    ~OperatorSaver() = default;
};

#endif //STACK_OPERATOR_SAVER_H
