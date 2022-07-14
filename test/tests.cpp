#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../source/executor.h"

TEST_CASE("Validator")
{
    SECTION("Name validation")
    {
        REQUIRE_NOTHROW(Validator::instance()->validateName("SET"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("PRINT VAL"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("PRINT EXPR"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("SAVE"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("PRINT EXPR ALL"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("PRINT VAL ALL"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("LOAD"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("++"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("--"));
        REQUIRE_NOTHROW(Validator::instance()->validateName("EXIT"));

        REQUIRE_THROWS(Validator::instance()->validateName("set"));
        REQUIRE_THROWS(Validator::instance()->validateName("1"));
        REQUIRE_THROWS(Validator::instance()->validateName("exit"));
        REQUIRE_THROWS(Validator::instance()->validateName("+++"));
        REQUIRE_THROWS(Validator::instance()->validateName("PRINT  VAL"));
    }

    SECTION("Argument validation")
    {
        vector<string> twoArgs, oneArg, emptyArg;
        twoArgs.emplace_back("arg1");
        twoArgs.emplace_back("arg2");
        oneArg.emplace_back("agr3");

        REQUIRE_NOTHROW(Validator::instance()->validateArgs("SET", twoArgs));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("PRINT VAL", oneArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("PRINT EXPR", oneArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("SAVE", oneArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("PRINT EXPR ALL", emptyArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("PRINT VAL ALL", emptyArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("LOAD", oneArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("++", oneArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("--", oneArg));
        REQUIRE_NOTHROW(Validator::instance()->validateArgs("EXIT", emptyArg));

        REQUIRE_THROWS(Validator::instance()->validateArgs("SET", emptyArg));
        REQUIRE_THROWS(Validator::instance()->validateArgs("PRINT VAL", twoArgs));
        REQUIRE_THROWS(Validator::instance()->validateArgs("PRINT EXPR", emptyArg));
        REQUIRE_THROWS(Validator::instance()->validateArgs("SAVE", twoArgs));
        REQUIRE_THROWS(Validator::instance()->validateArgs("PRINT EXPR ALL", oneArg));
        REQUIRE_THROWS(Validator::instance()->validateArgs("PRINT VAL ALL", twoArgs));
        REQUIRE_THROWS(Validator::instance()->validateArgs("LOAD", emptyArg));
        REQUIRE_THROWS(Validator::instance()->validateArgs("++", twoArgs));
        REQUIRE_THROWS(Validator::instance()->validateArgs("--", twoArgs));
        REQUIRE_THROWS(Validator::instance()->validateArgs("EXIT", oneArg));
    }
}

TEST_CASE("Command")
{
    SECTION("Constructor with parameters")
    {
        vector<string> args;
        args.emplace_back("arg1");
        args.emplace_back("srg2");

        Command c1(string("SET"), args);
        REQUIRE(c1.getName() == "SET");
        REQUIRE(c1.getArguments() == args);
    }

    SECTION("Copy constructor")
    {
        vector<string> args;
        args.emplace_back("arg1");
        args.emplace_back("arg2");

        Command c1(string("SET"), args);
        REQUIRE(c1.getName() == "SET");
        REQUIRE(c1.getArguments() == args);

        Command c2(c1);
        REQUIRE(c2.getName() == "SET");
        REQUIRE(c2.getArguments() == args);
    }

    SECTION("Copy assignment operator")
    {
        vector<string> args;
        args.emplace_back("arg1");
        args.emplace_back("srg2");

        Command c1(string("SET"), args);
        REQUIRE(c1.getName() == "SET");
        REQUIRE(c1.getArguments() == args);

        Command c2 = c1;
        REQUIRE(c2.getName() == "SET");
        REQUIRE(c2.getArguments() == args);
    }

    SECTION("Name getter and setter")
    {
        vector<string> args;

        Command c1(string("PRINT VAL ALL"), args);
        REQUIRE(c1.getName() == "PRINT VAL ALL");

        c1.setName("PRINT EXPR ALL");
        REQUIRE(c1.getName() == "PRINT EXPR ALL");
    }

    SECTION("Arguments getter and setter")
    {
        vector<string> args1, args2;
        args1.emplace_back("arg1");
        args2.emplace_back("arg2");

        Command c1(string("SAVE"), args1);
        REQUIRE(c1.getArguments() == args1);

        c1.setArguments(args2);
        REQUIRE(c1.getArguments() == args2);
    }

    SECTION("Argument count getter")
    {
        vector<string> args1, args2;
        args1.emplace_back("arg1");
        args1.emplace_back("arg2");

        args2.emplace_back("arg3");
        args2.emplace_back("arg4");

        Command c1("SET", args1);
        REQUIRE(c1.getArguments() == args1);
        REQUIRE(c1.argumentCount() == 2);

        c1.setArguments(args2);
        REQUIRE(c1.getArguments() == args2);
        REQUIRE(c1.argumentCount() == 2);
    }
}

TEST_CASE("Shunting-yard algorithm")
{
    SECTION("Addition") {
        const char* test = "3+5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == 8);
    }

    SECTION("Subtraction") {
        const char* test = "3-5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == (-2));
    }

    SECTION("Multiplication") {
        const char* test = "3*5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == 15);
    }

    SECTION("Division") {
        const char* test1 = "3/5";
        const char* test2 = "5/3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);
    }

    SECTION("Less than") {
        const char* test1 = "5 < 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);

        const char* test2 = "3 < 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);
    }

    SECTION("Greater than") {
        const char* test1 = "5 > 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "3 > 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 0);
    }

    SECTION("Equal") {
        const char* test1 = "5 == 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);

        const char* test2 = "5 == 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);

        const char* test3 = "5 = = 5";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test3));
    }

    SECTION("Not equal") {
        const char* test1 = "5 != 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "5 != 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 0);

        const char* test3 = "5 ! = 5";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test3));
    }

    SECTION("And") {
        const char* test1 = "5 and 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "5 and 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 0);

        const char* test3 = "0 and 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 0);
    }

    SECTION("Or") {
        const char* test1 = "5 or 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "5 or 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);

        const char* test3 = "0 or 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 0);
    }

    SECTION("Not") {
        const char* test1 = "not 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);

        const char* test2 = "not 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);

        const char* test3 = "not (3+5)";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 0);
    }

    SECTION("If") {
        const char* test1 = "if 5==5 ? 2 : 3;";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 2);

        const char* test2 = "if 5==3 ? 2 : 3;";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 3);
    }


    SECTION("Bracket expressions") {
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

    SECTION("Empty brackets") {
        const char* test = "()";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test));
    }

    SECTION("Mismatched brackets") {
        const char* test1 = "3+5)";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test1));

        const char* test2 = "(3+5";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test2));
    }

    SECTION("Complex expressions - value") {
        const char* test1 = "5/3*(5/2)-5*(4*3/(2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == (-20));
    }

    SECTION("Complex expressions - logic") {
        const char* test1 = "5/3*(5/2)>5*(4*3/(2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);

        const char* test2 = "5/3*(5/2)<5*(4*3/(2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);

        const char* test3 = "5/3*(5/2) == 5*(4*3/(2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 0);

        const char* test4 = "5/3*(5/2) != 5*(4*3/(2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test4) == 1);

        const char* test5 = "((4*9)/3)*5 and 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test5) == 0);

        const char* test6 = "(3+5)*42 and 1";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test6) == 1);

        const char* test7 = "8*5 or 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test7) == 1);

        const char* test8 = "7*6 or 1";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test8) == 1);
    }

    SECTION("Whitespace expressions") {
        const char* test = "5  /  3  * (   5 /   2 ) -5 *( 4* 3 /( 2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == (-20));
    }
}

