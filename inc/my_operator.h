#ifndef __MYOPERATOR_H__
#define __MYOPERATOR_H__

#include <stdexcept>
#include <vector>

using std::vector;

/**
 * @brief operator base class
 * 
 */
struct MyOperator {
    char symbol; // the symbol of the operator
    int priority; // the priority of the operator

    MyOperator(char sym, int pri) {
        symbol = sym;
        priority = pri;
    }
    
    virtual int calculate(int left, int right) const = 0;
    virtual ~MyOperator() {}
};

/**
 * @brief manages and picks available operators
 * 
 */
class OperatorPicker 
{
    vector<const MyOperator*> myOperators; //all registered operators

    OperatorPicker() {};
    OperatorPicker(const OperatorPicker&) = delete;
    OperatorPicker& operator= (const OperatorPicker&) = delete;

    const MyOperator* findOperator(char s) {
        for (const MyOperator* const& current : myOperators) {
            if (current->symbol == s) {return current;}
        }
        return nullptr;
    }

public:

    static OperatorPicker* instance() {
        static OperatorPicker i;
        return &i;
    }

    void add(const MyOperator* oper) {
        if (oper && !findOperator(oper->symbol)) {
            myOperators.push_back(oper);
        }
    }

    const MyOperator* pick(char s) {
        return findOperator(s);
    }
};

/**
 * @brief registers operators
 * 
 * @tparam DT operator
 */
template <typename DT>
class OperatorSaver {
private:
    DT oper; //the operator to be registered

public:
    OperatorSaver() {
        OperatorPicker::instance() -> add(&oper);
    }
};

#endif // __MYOPERATOR_H__
