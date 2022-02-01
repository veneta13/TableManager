#ifndef __COMMANDCREATOR_H__
#define __COMMANDCREATOR_H__

#include "command.h"

using std::vector;
using std::string;

/**
 * @brief generates commands
 *
 */
class CommandCreator {
    CommandCreator() = default;
    CommandCreator(const CommandCreator&) = delete;
    CommandCreator& operator= (const CommandCreator&) = delete;

public:
    static CommandCreator* instance() {
        static CommandCreator i;
        return &i;
    }

    Command* createCommand();
};

#endif // __COMMANDCREATOR_H__
