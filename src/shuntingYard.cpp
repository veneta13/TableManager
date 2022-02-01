#include "../inc/myOperator.h"
#include "../inc/expressionHandler.h"

#include <stack>
#include <stdexcept>
#include <cctype>

using std::stack;

/**
 * @brief read number from string
 * 
 * @param expr string position pointer
 * @return int the number value
 */
static int readNumber (const char *& expr) {
    int number = 0;
    while (std::isdigit(*expr)) {
        number *= 10;
        number += (*expr - '0');
        expr++;
    }
    return number;
}

/**
 * @brief calculate operators
 * 
 * @param numberStack the arguments
 * @param oper the operator
 */
static void calculate(stack<int>& numberStack, const MyOperator* oper) {
    if (oper->symbol == '(') {
        throw std::runtime_error("Error: cannot calculate (.");
    }
    int number1 = numberStack.top();
    numberStack.pop();
    if (oper->symbol == '~') {
        numberStack.push(oper->calculate(number1, 0));
        return;
    }
    int number2 = numberStack.top();
    numberStack.pop();
    numberStack.push(oper->calculate(number1, number2));
}

/**
 * @brief Get the Table Bound Adresses
 * 
 * @param expr the expression
 * @return vector<Address> the addresses
 */
vector<Address> getTableBoundAdresses(const char *&  expr) {
    std::string expression(expr);
    int pos1 = 0, pos2 = 0;

    if ((pos1 = expression.find(")")) != std::string::npos) {
        for (int i = 0; i < pos1+1; i++) {expr++;}
    }
    else {
        throw std::runtime_error("Error: error in sum function.");
    }

    assert((pos1 = expression.find("(")) != std::string::npos);
    expression.erase(0, pos1+1);
    assert(pos2 = expression.find(","));
    const char * add1 = expression.substr(0, pos2).c_str();
    Address address1(add1,
                     Table::instance()->getCurrentAddress().row,
                     Table::instance()->getCurrentAddress().column);
    expression.erase(0, pos2+1);

    assert((pos2 = expression.find(")")) != std::string::npos);
    assert(pos1 = expression.find(","));
    const char * add2 = expression.substr(pos1+1, pos2).c_str();
    Address address2(add2,
                     Table::instance()->getCurrentAddress().row,
                     Table::instance()->getCurrentAddress().column);

    if (address1.row > address2.row) {
        std::swap(address1.row, address2.row);
    }
    if (address1.column > address2.column) {
        std::swap(address1.column, address2.column);
    }

    vector<Address> result;
    result.push_back(address1);
    result.push_back(address2);
    return result;
} 

/**
 * @brief calculate the value of an expression with the Shunting-yard algorithm
 * 
 * @param expr the expression to be calculated
 * @return int the value of the expression
 */
int shuntingYard(const char* expr) {
    stack<int> numberStack;
    stack<const MyOperator*> operatorStack;
    OperatorPicker* opPicker = OperatorPicker::instance();

    while (*expr) {
        if (std::isspace(*expr)) {
            expr++;
            continue;
        }
        if (std::isdigit(*expr)) {
            int num = readNumber(expr);
            numberStack.push(num);
            continue;
        }
        if (*expr == '(') {
            const MyOperator* oper = opPicker->pick(*expr);
            operatorStack.push(oper);
            expr++;
            continue;
        }
        if (*expr == '+' || *expr == '-' || *expr == '/' || *expr == '*' ||
            *expr == '<' || *expr == '>' || *expr == '!' || *expr == '=') {
            const MyOperator* oper = opPicker->pick(*expr);
            if (!oper) {
                throw std::runtime_error("Error: Invalid operator!");
            }
            if (*expr == '=' || *expr == '!') {
                expr++;
                if (*expr != '=') {
                    throw std::runtime_error("Error: Invalid expression!");
                }
            }
            while (!operatorStack.empty() && operatorStack.top()->priority > oper->priority) {
                const MyOperator* tempOper = operatorStack.top();
                calculate(numberStack, tempOper);
                operatorStack.pop();
            }
            operatorStack.push(oper);
            expr++;
            continue;
        }
        if (*expr == ')') {
            while (!operatorStack.empty() && operatorStack.top()->symbol != '(') {
                const MyOperator * oper = operatorStack.top();
                calculate(numberStack, oper);
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() -> symbol == '(') {
                operatorStack.pop();
            }
            else {
                throw std::runtime_error("Error: mismatched brackets in expression!");
            }
            expr++;
            continue;
        }
        if (*expr == 'R') {
            Address address = Address(expr,
                                      Table::instance()->getCurrentAddress().row,
                                      Table::instance()->getCurrentAddress().column);
            if (address == Table::instance()->getCurrentAddress()) {
                throw std::runtime_error("Error: recursive cell formula!");
            }
            int num = Table::instance()->getCellValue(address);
            numberStack.push(num);
            continue;
        }
        if (*expr == 's' && *(++expr) == 'u' && *(++expr) == 'm') {
            vector<Address> addresses = getTableBoundAdresses(expr);
            int sum = 0;
            for (int r = addresses[0].row; r <= addresses[1].row; r++) {
                for (int c = addresses[0].column; c <= addresses[1].column; c++) {
                    Address address = Address(r, c);
                    sum += Table::instance()->getCellValue(address);
                }
            }
            numberStack.push(sum);
            continue;
        }
        if (*expr == 'c' && *(++expr) == 'o' && *(++expr) == 'u' && *(++expr) == 'n' && *(++expr) == 't') {
            vector<Address> addresses = getTableBoundAdresses(expr);
            int count = 0;
            for (int r = addresses[0].row; r <= addresses[1].row; r++) {
                for (int c = addresses[0].column; c <= addresses[1].column; c++) {
                    Address address = Address(r,c);
                    count += Table::instance()->getCell(address) == "" ? 0 : 1;
                }
            }
            numberStack.push(count);
            continue;
        }
        if (*expr == 'a' && *(++expr) == 'n' && *(++expr) == 'd') {
            const MyOperator* oper = opPicker->pick('&');
            if (!oper) {
                throw std::runtime_error("Error: Invalid operator!");
            }
            while (!operatorStack.empty() && operatorStack.top()->priority > oper->priority) {
                const MyOperator* tempOper = operatorStack.top();
                calculate(numberStack, tempOper);
                operatorStack.pop();
            }
            operatorStack.push(oper);
            expr++;
            continue;
        }
        if (*expr == 'n' && *(++expr) == 'o' && *(++expr) == 't') {
            const MyOperator* oper = opPicker->pick('~');
            if (!oper) {
                throw std::runtime_error("Error: Invalid operator!");
            }
            operatorStack.push(oper);
            expr++;
            continue;
        }
        if (*expr == 'o' && *(++expr) == 'r') {
            const MyOperator* oper = opPicker->pick('|');
            if (!oper) {
                throw std::runtime_error("Error: Invalid operator!");
            }
            while (!operatorStack.empty() && operatorStack.top()->priority > oper->priority) {
                const MyOperator* tempOper = operatorStack.top();
                calculate(numberStack, tempOper);
                operatorStack.pop();
            }
            operatorStack.push(oper);
            expr++;
            continue;
        }
        if (*expr == 'i' && *(++expr) == 'f') {
            std::string condition, trueClause, falseClause;
            int pos1 = 0, pos2 = 0;
            std::string expression(expr);

            if ((pos1 = expression.find(";")) != std::string::npos) {
                for (int i = 0; i < pos1+1; i++) {expr++;}
            }
            else {
                throw std::runtime_error("Error: if clause not closed with ;");
            }

            if ((pos2 = expression.find("?")) != std::string::npos) {
                pos1 = expression.find("f");
                expression.erase(0, pos1+1);
                condition = expression.substr(0, pos2-1);
                expression.erase(0, pos2+1);
                if ((pos1 = expression.find(":")) != std::string::npos) {
                    trueClause = expression.substr(0, pos1);
                    expression.erase(0, pos1 + 1);
                    pos1 = expression.find(";");
                    falseClause = expression.substr(0, pos1);
                }
                else {
                    throw std::runtime_error("Error: Invalid symbol in expression");
                }
            }
            else {
                throw std::runtime_error("Error: Invalid symbol in expression");
            }
            numberStack.push(shuntingYard(condition.c_str()) ?
                    shuntingYard(trueClause.c_str()) :
                    shuntingYard(falseClause.c_str()));
            continue;
        }
        throw std::runtime_error("Error: Invalid expression");
    }

    while(!operatorStack.empty()) {
        const MyOperator * oper = operatorStack.top();
        calculate(numberStack, oper);
        operatorStack.pop();
    }

    if (numberStack.empty()) {
        throw std::runtime_error("Error: Expression was not calculated correctly!");
    }

    int result = numberStack.top();
    numberStack.pop();

    if (!numberStack.empty()) {
        throw std::runtime_error("Error: Expression was not calculated correctly!");
    }

    return result;
}
