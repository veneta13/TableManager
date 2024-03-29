#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "command_creator.h"
#include "table.h"

#include <iomanip>
#include <fstream>
#include <iostream>

/// Executor for user input | Singleton
class Executor {
    /// Flag showing if the program should be terminated
    bool exit = false;

    Executor();

    void set(vector<string>& args) const;
    void printVal(vector<string>& args) const;
    void printExpr(vector<string>& args) const;
    void printExprAll() const;
    void printValAll() const;
    void save(vector<string>& args) const;
    void load(vector<string>& args) const;
    void increase(vector<string>& args) const;
    void decrease(vector<string>& args) const;

    void incrDecrHelper(Address &address, int &intValue) const;

    void printCellVal(Address &address) const;
    void printCellExpr(Address &address) const;
    void printExpression(Address& address) const;
    void printValue(Address& address) const;
    void printColumnLine(int iteration, int times) const;

public:
    Executor(const Executor&) = delete;
    Executor& operator= (const Executor&) = delete;

    static Executor* instance();

    bool isExit() const;
    void execute();
};

#endif // __EXECUTOR_H__
