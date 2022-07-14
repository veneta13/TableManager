#ifndef STACK_OPERATOR_SAVER_H
#define STACK_OPERATOR_SAVER_H

#include "operator_picker.h"

/// @brief Operator adder template
/// \tparam DT placeholder for operator types
template <typename DT>
class OperatorSaver {
private:
    /// Operator to be registered
    DT currentOperator;

public:
    OperatorSaver() {
        OperatorPicker::instance() -> add(&currentOperator);
    }

    OperatorSaver(OperatorSaver const& other) = delete;
    OperatorSaver& operator=(OperatorSaver const& other) = delete;
    ~OperatorSaver() = default;
};

#endif //STACK_OPERATOR_SAVER_H
