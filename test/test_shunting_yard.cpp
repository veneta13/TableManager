#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../inc/expression_handler.h"

TEST_CASE("Addition") {
    const char* test = "3+5";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == 8);
}

TEST_CASE("Subtraction") {
    const char* test = "3-5";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == (-2));
}

TEST_CASE("Multiplication") {
    const char* test = "3*5";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == 15);
}

TEST_CASE("Division") {
    const char* test1 = "3/5";
    const char* test2 = "5/3";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);
}

TEST_CASE("Less than") {
    const char* test1 = "5 < 3";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 0);

    const char* test2 = "3 < 5";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 1);
}

TEST_CASE("Greater than") {
    const char* test1 = "5 > 3";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 1);

    const char* test2 = "3 > 5";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 0);
}

TEST_CASE("Equal") {
    const char* test1 = "5 == 3";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 0);

    const char* test2 = "5 == 5";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 1);

    const char* test3 = "5 = = 5";
    REQUIRE_THROWS (ExpressionHandler::instance()->shuntingYard(test3));
}

TEST_CASE("Not equal") {
    const char* test1 = "5 != 3";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 1);

    const char* test2 = "5 != 5";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 0);

    const char* test3 = "5 ! = 5";
    REQUIRE_THROWS (ExpressionHandler::instance()->shuntingYard(test3));
}

TEST_CASE("And") {
    const char* test1 = "5 and 3";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 1);

    const char* test2 = "5 and 0";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 0);

    const char* test3 = "0 and 0";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test3) == 0);
}

TEST_CASE("Or") {
    const char* test1 = "5 or 3";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 1);

    const char* test2 = "5 or 0";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 1);

    const char* test3 = "0 or 0";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test3) == 0);
}

TEST_CASE("Not") {
    const char* test1 = "not 3";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 0);

    const char* test2 = "not 0";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 1);

    const char* test3 = "not (3+5)";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test3) == 0);
}

TEST_CASE("If") {
    const char* test1 = "if 5==5 ? 2 : 3;";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 2);

    const char* test2 = "if 5==3 ? 2 : 3;";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 3);
}


TEST_CASE("Bracket expressions") {
    const char* test1 = "(3+5)";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 8);

    const char* test2 = "(3-5)";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == (-2));

    const char* test3 = "(3*5)";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 15);

    const char* test4 = "(3/5)";
    const char* test5 = "(5/3)";
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test4) == 0);
    REQUIRE(ExpressionHandler::instance()->shuntingYard(test5) == 1);
}

TEST_CASE("Empty brackets") {
    const char* test = "()";
    REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test));
}

TEST_CASE("Mismatched brackets") {
    const char* test1 = "3+5)";
    REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test1));

    const char* test2 = "(3+5";
    REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test2));
}

TEST_CASE("Complex expressions - value") {
    const char* test1 = "5/3*(5/2)-5*(4*3/(2))";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == (-20));
}

TEST_CASE("Complex expressions - logic") {
    const char* test1 = "5/3*(5/2)>5*(4*3/(2))";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test1) == 0);

    const char* test2 = "5/3*(5/2)<5*(4*3/(2))";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test2) == 1);

    const char* test3 = "5/3*(5/2) == 5*(4*3/(2))";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test3) == 0);

    const char* test4 = "5/3*(5/2) != 5*(4*3/(2))";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test4) == 1);

    const char* test5 = "((4*9)/3)*5 and 0";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test5) == 0);

    const char* test6 = "(3+5)*42 and 1";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test6) == 1);

        const char* test7 = "8*5 or 0";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test7) == 1);

    const char* test8 = "7*6 or 1";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test8) == 1);
}

TEST_CASE("Whitespace expressions") {
    const char* test = "5  /  3  * (   5 /   2 ) -5 *( 4* 3 /( 2))";
    REQUIRE (ExpressionHandler::instance()->shuntingYard(test) == (-20));
}
