all: main shuntingYardTest

main: src/shuntingYard.cpp src/myOperator.cpp main.cpp src/command.cpp src/commandCreator.cpp src/executor.cpp src/tableAddress.cpp  src/validator.cpp src/table.cpp src/executorHelperFunctions.cpp
	g++ src/shuntingYard.cpp src/myOperator.cpp main.cpp src/command.cpp src/commandCreator.cpp src/executor.cpp src/tableAddress.cpp  src/validator.cpp src/table.cpp src/executorHelperFunctions.cpp

shuntingYardTest: src/shuntingYard.cpp src/myOPerator.cpp test/TEST_shuntingYard.cpp src/table.cpp src/tableAddress.cpp
	g++ src/shuntingYard.cpp src/myOPerator.cpp test/TEST_shuntingYard.cpp src/table.cpp src/tableAddress.cpp