cmake_minimum_required(VERSION 3.0.0)
project(table-manager VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
        tests
        test/tests.cpp
        source/command.cpp
        source/command_creator.cpp
        source/executor.cpp
        source/my_operator.cpp
        source/expression_handler.cpp
        source/table.cpp
        source/table_address.cpp
        source/validator.cpp
        source/operator_picker.cpp
        source/operator_saver.cpp
        source/operators.cpp
        source/table_hash.cpp
)

add_executable(
        main
        source/main.cpp
        source/command.cpp
        source/command_creator.cpp
        source/executor.cpp
        source/my_operator.cpp
        source/expression_handler.cpp
        source/table.cpp
        source/table_address.cpp
        source/validator.cpp
        source/operator_picker.cpp
        source/operator_saver.cpp
        source/operators.cpp
        source/table_hash.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)