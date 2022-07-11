cmake_minimum_required(VERSION 3.0.0)
project(stack VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
        tests
        test/test_shunting_yard.cpp
        src/command.cpp
        src/commandCreator.cpp
        src/executor.cpp
        src/executorHelperFunctions.cpp
        src/myOperator.cpp
        src/shuntingYard.cpp
        src/table.cpp
        src/tableAddress.cpp
        src/validator.cpp
)

add_executable(
        main
        src/main.cpp
        src/command.cpp
        src/commandCreator.cpp
        src/executor.cpp
        src/executorHelperFunctions.cpp
        src/myOperator.cpp
        src/shuntingYard.cpp
        src/table.cpp
        src/tableAddress.cpp
        src/validator.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)