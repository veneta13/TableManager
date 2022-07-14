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

TEST_CASE("Operator classes")
{
    SECTION("Addition")
    {
        Addition a;
        REQUIRE(a.priority == 5);
        REQUIRE(a.symbol == '+');
    }

    SECTION("Subtraction")
    {
        Subtraction s;
        REQUIRE(s.priority == 5);
        REQUIRE(s.symbol == '-');
    }

    SECTION("Multiplication")
    {
        Multiplication m;
        REQUIRE(m.priority == 10);
        REQUIRE(m.symbol == '*');
    }

    SECTION("Division")
    {
        Division d;
        REQUIRE(d.priority == 10);
        REQUIRE(d.symbol == '/');
    }

    SECTION("Opening bracket")
    {
        BracketOpen b;
        REQUIRE(b.priority == 2);
        REQUIRE(b.symbol == '(');
    }

    SECTION("Closing bracket")
    {
        BracketClose b;
        REQUIRE(b.priority == 50);
        REQUIRE(b.symbol == ')');
    }

    SECTION("Less than")
    {
        LessThan l;
        REQUIRE(l.priority == 0);
        REQUIRE(l.symbol == '<');
    }

    SECTION("Greater than")
    {
        GreaterThan g;
        REQUIRE(g.priority == 0);
        REQUIRE(g.symbol == '>');
    }

    SECTION("Not equal")
    {
        NotEqual n;
        REQUIRE(n.priority == 0);
        REQUIRE(n.symbol == '!');
    }

    SECTION("Equal")
    {
        Equal e;
        REQUIRE(e.priority == 0);
        REQUIRE(e.symbol == '=');
    }

    SECTION("And")
    {
        And a;
        REQUIRE(a.priority == 1);
        REQUIRE(a.symbol == '&');
    }

    SECTION("Or")
    {
        Or o;
        REQUIRE(o.priority == 1);
        REQUIRE(o.symbol == '|');
    }

    SECTION("Not")
    {
        Not n;
        REQUIRE(n.priority == 100);
        REQUIRE(n.symbol == '~');
    }
}

TEST_CASE("Address")
{
    SECTION("Constructor with row and column parameters")
    {
        Address a(1, 2);
        REQUIRE(a.row == 1);
        REQUIRE(a.column == 2);
    }

    SECTION("Constructor for absolute address")
    {
        const char* text = "R5C3";
        Address a(text);
        REQUIRE(a.row == 5);
        REQUIRE(a.column == 3);
    }

    SECTION("Constructor for relative address")
    {
        const char* text = "R[5]C[-3]";
        Address a(text, 10, 7);
        REQUIRE(a.row == 15);
        REQUIRE(a.column == 4);
    }

    SECTION("Operator ==")
    {
        Address a(2, 5), b(2, 5), c(2, 6), d(3, 5), e(9, 4);
        REQUIRE(a == b);
        REQUIRE(!(a == c));
        REQUIRE(!(a == d));
        REQUIRE(!(a == e));
    }
}

TEST_CASE("Shunting-yard algorithm")
{
    SECTION("Text")
    {
        const char* test1 = "\"5\"";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test2));

        const char* test2 = "\"abc\"";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test2));
    }

    SECTION("Addition")
    {
        const char* test = "3+5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == 8);
    }

    SECTION("Subtraction")
    {
        const char* test = "3-5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == (-2));
    }

    SECTION("Multiplication")
    {
        const char* test = "3*5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == 15);
    }

    SECTION("Division")
    {
        const char* test1 = "3/5";
        const char* test2 = "5/3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);
    }

    SECTION("Less than")
    {
        const char* test1 = "5 < 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);

        const char* test2 = "3 < 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);
    }

    SECTION("Greater than")
    {
        const char* test1 = "5 > 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "3 > 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 0);
    }

    SECTION("Equal")
    {
        const char* test1 = "5 == 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);

        const char* test2 = "5 == 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);

        const char* test3 = "5 = = 5";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test3));
    }

    SECTION("Not equal")
    {
        const char* test1 = "5 != 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "5 != 5";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 0);

        const char* test3 = "5 ! = 5";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test3));
    }

    SECTION("And")
    {
        const char* test1 = "5 and 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "5 and 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 0);

        const char* test3 = "0 and 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 0);
    }

    SECTION("Or")
    {
        const char* test1 = "5 or 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 1);

        const char* test2 = "5 or 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);

        const char* test3 = "0 or 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 0);
    }

    SECTION("Not")
    {
        const char* test1 = "not 3";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 0);

        const char* test2 = "not 0";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 1);

        const char* test3 = "not (3+5)";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test3) == 0);
    }

    SECTION("If")
    {
        const char* test1 = "if 5==5 ? 2 : 3;";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == 2);

        const char* test2 = "if 5==3 ? 2 : 3;";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test2) == 3);
    }


    SECTION("Bracket expressions")
    {
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

    SECTION("Empty brackets")
    {
        const char* test = "()";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test));
    }

    SECTION("Mismatched brackets")
    {
        const char* test1 = "3+5)";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test1));

        const char* test2 = "(3+5";
        REQUIRE_THROWS(ExpressionHandler::instance()->shuntingYard(test2));
    }

    SECTION("Complex expressions - value")
    {
        const char* test1 = "5/3*(5/2)-5*(4*3/(2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test1) == (-20));
    }

    SECTION("Complex expressions - logic")
    {
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

    SECTION("Whitespace expressions")
    {
        const char* test = "5  /  3  * (   5 /   2 ) -5 *( 4* 3 /( 2))";
        REQUIRE(ExpressionHandler::instance()->shuntingYard(test) == (-20));
    }
}

TEST_CASE("Table")
{
    SECTION("Setter and getters for table cell")
    {
        Address a1(2, 3), a2(2, 4), a3(3, 1);

        Table::instance()->setCell(a1, "\"6\"");
        REQUIRE(Table::instance()->getCell(a1) == "\"6\"");
        REQUIRE(Table::instance()->getCellValue(a1) == 0);

        Table::instance()->setCell(a2, "6");
        REQUIRE(Table::instance()->getCell(a2) == "6");
        REQUIRE(Table::instance()->getCellValue(a2) == 6);

        Table::instance()->setCell(a3, "6*3");
        REQUIRE(Table::instance()->getCell(a3) == "6*3");
        REQUIRE(Table::instance()->getCellValue(a3) == 18);
    }

    SECTION("Getter for max address")
    {
        REQUIRE(Table::instance()->getMaxAddress() == Address{3, 4});

        Table::instance()->setCell(Address{10, 10}, "2");
        REQUIRE(Table::instance()->getMaxAddress() == Address{10, 10});

        Table::instance()->setCell(Address{11, 9}, "3");
        REQUIRE(Table::instance()->getMaxAddress() == Address{11, 10});

        Table::instance()->setCell(Address{8, 13}, "3");
        REQUIRE(Table::instance()->getMaxAddress() == Address{11, 13});
    }

    SECTION("Getter and setter for current address")
    {
        REQUIRE(Table::instance()->getCurrentAddress() == Address{0, 0});

        Table::instance()->setCurrentAddress(Address{1, 2});
        REQUIRE(Table::instance()->getCurrentAddress() == Address{1, 2});

        Table::instance()->setCurrentAddress(Address{3, 4});
        REQUIRE(Table::instance()->getCurrentAddress() == Address{3, 4});
    }
}
