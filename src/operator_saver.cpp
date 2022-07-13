#include "../inc/operator_saver.h"

static OperatorSaver<Addition> registrationAddition;
static OperatorSaver<Subtraction> registrationSubtraction;
static OperatorSaver<Multiplication> registrationMultiplication;
static OperatorSaver<Division> registrationDivision;
static OperatorSaver<BracketOpen> registrationBracketOpen;
static OperatorSaver<BracketClose> registrationBracketClose;
static OperatorSaver<LessThan> registrationLessThan;
static OperatorSaver<GreaterThan> registrationGreaterThan;
static OperatorSaver<NotEqual> registrationNotEqual;
static OperatorSaver<Equal> registrationEqual;
static OperatorSaver<And> registrationAnd;
static OperatorSaver<Or> registrationOr;
static OperatorSaver<Not> registrationNot;
