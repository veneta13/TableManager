#ifndef STACK_OPERATORS_H
#define STACK_OPERATORS_H

#include "my_operator.h"


/// The + operator
struct Addition : public MyOperator
{
    Addition();
    Addition(Addition const& other) = delete;
    Addition& operator=(Addition const& other) = delete;
    ~Addition();

    int calculate (int right, int left) const override;
};



/// The - operator
struct Subtraction : public MyOperator
{
    Subtraction();
    Subtraction(Subtraction const& other) = delete;
    Subtraction& operator=(Subtraction const& other) = delete;
    ~Subtraction();

    int calculate (int right, int left) const override;
};



/// The * operator
struct Multiplication : public MyOperator
{
    Multiplication();
    Multiplication(Multiplication const& other) = delete;
    Multiplication& operator=(Multiplication const& other) = delete;
    ~Multiplication();

    int calculate (int right, int left) const override;
};



/// The / operator
struct Division : public MyOperator
{
    Division();
    Division(Division const& other) = delete;
    Division& operator=(Division const& other) = delete;
    ~Division();

    int calculate (int right, int left) const override;
};



/// The ( operator
struct BracketOpen : public MyOperator
{
    BracketOpen();
    BracketOpen(BracketOpen const& other) = delete;
    BracketOpen& operator=(BracketOpen const& other) = delete;
    ~BracketOpen();

    int calculate (int right, int left) const override;
};



/// The ) operator
struct BracketClose : public MyOperator
{
    BracketClose();
    BracketClose(BracketClose const& other) = delete;
    BracketClose& operator=(BracketClose const& other) = delete;
    ~BracketClose();

    int calculate (int right, int left) const override;
};



/// The < operator
struct LessThan : public MyOperator
{
    LessThan();
    LessThan(LessThan const& other) = delete;
    LessThan& operator=(LessThan const& other) = delete;
    ~LessThan();

    int calculate (int right, int left) const override;
};



/// The > operator
struct GreaterThan : public MyOperator
{
    GreaterThan();
    GreaterThan(GreaterThan const& other) = delete;
    GreaterThan& operator=(GreaterThan const& other) = delete;
    ~GreaterThan();

    int calculate (int right, int left) const override;
};



/// The != operator
struct NotEqual : public MyOperator
{
    NotEqual();
    NotEqual(NotEqual const& other) = delete;
    NotEqual& operator=(NotEqual const& other) = delete;
    ~NotEqual();

    int calculate (int right, int left) const override;
};



/// The == operator
struct Equal : public MyOperator
{
    Equal();
    Equal(Equal const& other) = delete;
    Equal& operator=(Equal const& other) = delete;
    ~Equal();

    int calculate (int right, int left) const override;
};



/// The && operator
struct And : public MyOperator
{
    And();
    And(And const& other) = delete;
    And& operator=(And const& other) = delete;
    ~And();

    int calculate (int right, int left) const override;
};



/// The || operator
struct Or : public MyOperator
{
    Or();
    Or(Or const& other) = delete;
    Or& operator=(Or const& other) = delete;
    ~Or();

    int calculate (int right, int left) const override;
};



/// The ~ operator
struct Not : public MyOperator
{
    Not();
    Not(Not const& other) = delete;
    Not& operator=(Not const& other) = delete;
    ~Not();

    int calculate (int right, int left) const override;
};

#endif //STACK_OPERATORS_H
