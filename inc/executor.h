#ifndef __EXECUTOR_H__
#define __EXECUTOR_H__

#include "commandCreator.h"
#include "table.h"
#include "executorHelperFunctions.h"

#include <iomanip>
#include <fstream>

/**
 * @brief creates and executes commands
 * 
 */
class Executor {
    bool exit = false; // exit flag

    Executor() = default;
    Executor(const Executor&) = delete;
    Executor& operator= (const Executor&) = delete;

    void set(vector<string>& args);
    void printVal(vector<string>& args);
    void printExpr(vector<string>& args);
    void printExprAll();
    void printValAll();
    void save(vector<string>& args);
    void load(vector<string>& args);
    void increase(vector<string>& args);
    void decrease(vector<string>& args);

public:
    static Executor* instance() {
        static Executor i;
        return &i;
    }

    bool isExit();
    void execute();
};

#endif // __EXECUTOR_H__
