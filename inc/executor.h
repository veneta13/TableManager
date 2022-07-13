#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "commandCreator.h"
#include "table.h"

#include <iomanip>
#include <fstream>


/// Executor for user input | Singleton
class Executor {
    bool exit = false; // flag showing if the program should be terminated

    Executor() = default;

    void set(vector<string>& args);
    void printVal(vector<string>& args);
    void printExpr(vector<string>& args);
    void printExprAll();
    void printValAll();
    void save(vector<string>& args);
    void load(vector<string>& args);
    void increase(vector<string>& args);
    void decrease(vector<string>& args);

    void printExpression(Address address);
    void printValue(Address address);
    void printColumnLine(int iteration, int times);

public:
    Executor(const Executor&) = delete;
    Executor& operator= (const Executor&) = delete;

    static Executor* instance() {
        static Executor i;
        return &i;
    }

    bool isExit();
    void execute();
};

#endif // __EXECUTOR_H__
