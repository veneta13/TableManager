#ifndef __EXPRESSIONHANDLER_H__
#define __EXPRESSIONHANDLER_H__

#include "tableAddress.h"
#include "table.h"

#include <cassert>

int shuntingYard(const char* expr);

#endif // __EXPRESSIONHANDLER_H__
