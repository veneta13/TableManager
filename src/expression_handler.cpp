#include "../inc/ExpressionHandler.h"


/// Extract number from string
/// \param expr string to search in
/// \return extracted number
int ExpressionHandler::readNumber(const char *&expr) const {
    int number = 0;
    while (std::isdigit(*expr)) {
        number *= 10;
        number += (*expr - '0');
        expr++;
    }
    return number;
}


/// Calculate subexpression
/// \param numberStack numbers to calculate
/// \param currentOperator operator to calculate for
void ExpressionHandler::calculate(stack<int> &numberStack, const MyOperator *currentOperator) const {
    if (currentOperator->symbol == '(') {
        throw std::runtime_error("Error: cannot calculate (.");
    }

    int number1 = numberStack.top();
    numberStack.pop();

    if (currentOperator->symbol == '~') {
        numberStack.push(currentOperator->calculate(number1, 0));
        return;
    }

    int number2 = numberStack.top();
    numberStack.pop();
    numberStack.push(currentOperator->calculate(number1, number2));
}


/// Extract table-bound addresses
/// \param expr expression to extract addresses from
/// \return extracted cell addresses
vector<Address> ExpressionHandler::getTableBoundAddresses(const char *&expr) const {
    std::string expression(expr);
    int pos1, pos2; // expression position pointer

    if ((pos1 = expression.find(')')) != std::string::npos) {
        for (int i = 0; i < pos1 + 1; i++) { expr++; }
    } else {
        throw std::runtime_error("Error: error in sum function.");
    }

    assert((pos1 = expression.find('(')) != std::string::npos);
    expression.erase(0, pos1 + 1);
    assert(pos2 = expression.find(','));

    const char *addressCStr1 = expression.substr(0, pos2).c_str();
    Address address1(addressCStr1,
                     Table::instance()->getCurrentAddress().row,
                     Table::instance()->getCurrentAddress().column);
    expression.erase(0, pos2 + 1);

    assert((pos2 = expression.find(')')) != std::string::npos);
    assert(pos1 = expression.find(','));

    const char *addressCStr2 = expression.substr(pos1 + 1, pos2).c_str();
    Address address2(addressCStr2,
                     Table::instance()->getCurrentAddress().row,
                     Table::instance()->getCurrentAddress().column);

    if (address1.row > address2.row) { std::swap(address1.row, address2.row); }
    if (address1.column > address2.column) { std::swap(address1.column, address2.column); }

    vector<Address> result;
    result.push_back(address1);
    result.push_back(address2);
    return result;
}


/// Calculate the value of an expression with the Shunting-yard algorithm
/// \param expr expression to calculate
/// \return value of the expression
int ExpressionHandler::shuntingYard(const char *expr) const {
    stack<int> numberStack;
    stack<const MyOperator *> operatorStack;

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
            const MyOperator *currentOperator = OperatorPicker::instance()->pick(*expr);
            operatorStack.push(currentOperator);
            expr++;
            continue;
        }
        if (*expr == '+' || *expr == '-' || *expr == '/' || *expr == '*' ||
            *expr == '<' || *expr == '>' || *expr == '!' || *expr == '=') {
            const MyOperator *currentOperator = OperatorPicker::instance()->pick(*expr);
            if (!currentOperator) {
                throw std::runtime_error("Error: Invalid operator!");
            }
            if (*expr == '=' || *expr == '!') {
                expr++;
                if (*expr != '=') {
                    throw std::runtime_error("Error: Invalid expression!");
                }
            }
            while (!operatorStack.empty() && operatorStack.top()->priority > currentOperator->priority) {
                const MyOperator *tempOperator = operatorStack.top();
                calculate(numberStack, tempOperator);
                operatorStack.pop();
            }
            operatorStack.push(currentOperator);
            expr++;
            continue;
        }
        if (*expr == ')') {
            while (!operatorStack.empty() && operatorStack.top()->symbol != '(') {
                const MyOperator *currentOperator = operatorStack.top();
                calculate(numberStack, currentOperator);
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top()->symbol == '(') {
                operatorStack.pop();
            } else {
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
            sumShuntingYard(numberStack, expr);
            continue;
        }
        if (*expr == 'c' && *(++expr) == 'o' && *(++expr) == 'u' && *(++expr) == 'n' && *(++expr) == 't') {
            countShuntingYard(numberStack, expr);
            continue;
        }
        if (*expr == 'a' && *(++expr) == 'n' && *(++expr) == 'd') {
            andShuntingYard(operatorStack, numberStack);
            expr++;
            continue;
        }
        if (*expr == 'n' && *(++expr) == 'o' && *(++expr) == 't') {
            notShuntingYard(operatorStack);
            expr++;
            continue;
        }
        if (*expr == 'o' && *(++expr) == 'r') {
            orShuntingYard(operatorStack, numberStack);
            expr++;
            continue;
        }
        if (*expr == 'i' && *(++expr) == 'f') {
            ifShuntingYard(operatorStack, numberStack, expr);
            continue;
        }
        throw std::runtime_error("Error: Invalid expression");
    }

    while (!operatorStack.empty()) {
        const MyOperator *currentOperator = operatorStack.top();
        calculate(numberStack, currentOperator);
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


/// Shunting-yard helper function for sum
/// \param numberStack
/// \param expr
void ExpressionHandler::sumShuntingYard(stack<int> &numberStack, const char *expr) const {
    vector<Address> addresses = getTableBoundAddresses(expr);
    int sum = 0;

    for (int r = addresses[0].row; r <= addresses[1].row; r++) {
        for (int c = addresses[0].column; c <= addresses[1].column; c++) {
            Address address = Address(r, c);
            sum += Table::instance()->getCellValue(address);
        }
    }

    numberStack.push(sum);
}

void ExpressionHandler::countShuntingYard(stack<int> &numberStack, const char *expr) const {
    vector<Address> addresses = getTableBoundAddresses(expr);
    int count = 0;
    for (int r = addresses[0].row; r <= addresses[1].row; r++) {
        for (int c = addresses[0].column; c <= addresses[1].column; c++) {
            Address address = Address(r, c);
            count += Table::instance()->getCell(address).empty() ? 0 : 1;
        }
    }
    numberStack.push(count);
}

void ExpressionHandler::andShuntingYard(stack<const MyOperator *> &operatorStack, stack<int> &numberStack) const {
    const MyOperator *currentOperator = OperatorPicker::instance()->pick('&');
    if (!currentOperator) {
        throw std::runtime_error("Error: Invalid operator!");
    }

    while (!operatorStack.empty() && operatorStack.top()->priority > currentOperator->priority) {
        const MyOperator *tempOperator = operatorStack.top();
        calculate(numberStack, tempOperator);
        operatorStack.pop();
    }
    operatorStack.push(currentOperator);
}


void ExpressionHandler::notShuntingYard(stack<const MyOperator *> &operatorStack) const {
    const MyOperator *currentOperator = OperatorPicker::instance()->pick('~');
    if (!currentOperator) {
        throw std::runtime_error("Error: Invalid operator!\n");
    }
    operatorStack.push(currentOperator);
}

void ExpressionHandler::orShuntingYard(stack<const MyOperator *> &operatorStack, stack<int> &numberStack) const {
    const MyOperator *currentOperator = OperatorPicker::instance()->pick('|');
    if (!currentOperator) {
        throw std::runtime_error("Error: Invalid operator!\n");
    }
    while (!operatorStack.empty() && operatorStack.top()->priority > currentOperator->priority) {
        const MyOperator *tempOperator = operatorStack.top();
        calculate(numberStack, tempOperator);
        operatorStack.pop();
    }
    operatorStack.push(currentOperator);
}

void ExpressionHandler::ifShuntingYard(stack<const MyOperator *> &operatorStack,
                                       stack<int> &numberStack,
                                       const char* expr) const {
    std::string condition, trueClause, falseClause;
    int pos1 = 0, pos2 = 0;
    std::string expression(expr);

    if ((pos1 = expression.find(';')) != std::string::npos) {
        for (int i = 0; i < pos1 + 1; i++) {
            expr++;
        }
    }
    else {
        throw std::runtime_error("Error: if clause not closed with ;\n");
    }

    if ((pos2 = expression.find('?')) != std::string::npos) {
        pos1 = expression.find('f');
        expression.erase(0, pos1 + 1);
        condition = expression.substr(0, pos2 - 1);
        expression.erase(0, pos2 + 1);

        if ((pos1 = expression.find(':')) != std::string::npos) {
            trueClause = expression.substr(0, pos1);
            expression.erase(0, pos1 + 1);
            pos1 = expression.find(';');
            falseClause = expression.substr(0, pos1);
        }
        else {
            throw std::runtime_error("Error: Invalid symbol in expression\n");
        }

    }
    else {
        throw std::runtime_error("Error: Invalid symbol in expression\n");
    }

    numberStack.push(shuntingYard(condition.c_str()) ?
                     shuntingYard(trueClause.c_str()) :
                     shuntingYard(falseClause.c_str()));
}