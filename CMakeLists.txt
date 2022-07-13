cmake_minimum_required(VERSION 3.0.0)
project(table-manager VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(
        tests
        test/test_shunting_yard.cpp
        src/command.cpp
        src/command_creator.cpp
        src/executor.cpp
        src/my_operator.cpp
        src/expression_handler.cpp
        src/table.cpp
        src/table_address.cpp
        src/validator.cpp
        src/operator_picker.cpp
        src/operator_saver.cpp
        src/operators.cpp
        src/table_hash.cpp
)

add_executable(
        main
        src/main.cpp
        src/command.cpp
        src/command_creator.cpp
        src/executor.cpp
        src/my_operator.cpp
        src/expression_handler.cpp
        src/table.cpp
        src/table_address.cpp
        src/validator.cpp
        src/operator_picker.cpp
        src/operator_saver.cpp
        src/operators.cpp
        src/table_hash.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)