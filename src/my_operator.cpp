#include "../inc/my_operator.h"

/**
 * @brief the + operator
 * 
 */
struct Addition : public MyOperator
{
    Addition() : MyOperator('+', 5) {}
    int calculate (int right, int left) const override {
        return left + right;
    }
};
static OperatorSaver<Addition> registrationAddition;

/**
 * @brief the - operator
 * 
 */
struct Subtraction : public MyOperator
{
    Subtraction() : MyOperator('-', 5) {}
    int calculate (int right, int left) const override {
        return left - right;
    }
};
static OperatorSaver<Subtraction> registrationSubtraction;

/**
 * @brief the * operator
 * 
 */
struct Multiplication : public MyOperator
{
    Multiplication() : MyOperator('*', 10) {}
    int calculate (int right, int left) const override {
        return left * right;
    }
};
static OperatorSaver<Multiplication> registrationMultiplication;

/**
 * @brief the / operator
 * 
 */
struct Division : public MyOperator
{
    Division() : MyOperator('/', 10) {}
    int calculate (int right, int left) const override {
        return left / right;
    }
};
static OperatorSaver<Division> registrationDivision;

/**
 * @brief the ( operator
 * 
 */
struct BracketOpen : public MyOperator
{
    BracketOpen() : MyOperator('(', 2) {}
    int calculate (int right, int left) const override {
        throw std::runtime_error("Error: trying to calculate (!");
    }
};
static OperatorSaver<BracketOpen> registrationBracketOpen;

/**
 * @brief the ) operator
 * 
 */
struct BracketClose : public MyOperator
{
    BracketClose() : MyOperator(')', 50) {}
    int calculate (int right, int left) const override {
        throw std::runtime_error("Error: trying to calculate )!");
    }
};
static OperatorSaver<BracketClose> registrationBracketClose;

/**
 * @brief the < operator
 * 
 */
struct LessThan : public MyOperator
{
    LessThan() : MyOperator('<', 0) {}
    int calculate (int right, int left) const override {
        return left < right;
    }
};
static OperatorSaver<LessThan> registrationLessThan;

/**
 * @brief the > operator
 * 
 */
struct GreaterThan : public MyOperator
{
    GreaterThan() : MyOperator('>', 0) {}
    int calculate (int right, int left) const override {
        return left > right;
    }
};
static OperatorSaver<GreaterThan> registrationGreaterThan;

/**
 * @brief the != operator
 * 
 */
struct NotEqual : public MyOperator
{
    NotEqual() : MyOperator('!', 0) {}
    int calculate (int right, int left) const override {
        return left != right;
    }
};
static OperatorSaver<NotEqual> registrationNotEqual;

/**
 * @brief the == operator
 * 
 */
struct Equal : public MyOperator
{
    Equal() : MyOperator('=', 0) {}
    int calculate (int right, int left) const override {
        return left == right;
    }
};
static OperatorSaver<Equal> registrationEqual;

/**
 * @brief the && operator
 * 
 */
struct And : public MyOperator
{
    And() : MyOperator('&', 1) {}
    int calculate (int right, int left) const override {
        return left && right;
    }
};
static OperatorSaver<And> registrationAnd;

/**
 * @brief the || operator
 * 
 */
struct Or : public MyOperator
{
    Or() : MyOperator('|', 1) {}
    int calculate (int right, int left) const override {
        return left || right;
    }
};
static OperatorSaver<Or> registrationOr;

/**
 * @brief the ~ operator
 * 
 */
struct Not : public MyOperator
{
    Not() : MyOperator('~', 100) {}
    int calculate (int right = 0, int left = 0) const override {
        return right == 0 ? 1 : 0;
    }
};
static OperatorSaver<Not> registrationNot;
