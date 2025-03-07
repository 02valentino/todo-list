add_subdirectory(googletest)

set(GTEST_SOURCE_DIR googletest/googletest)

message(${GTEST_SOURCE_DIR}/include)

include_directories(${GTEST_SOURCE_DIR}/include ${GTEST_SOURCE_DIR})

set(TEST_SOURCES run_all_tests.cpp test_todo_class.cpp test_controller_class.cpp test_todo_list_class.cpp)

add_executable(run_all_tests ${TEST_SOURCES})

target_link_libraries(run_all_tests core)

target_link_libraries(run_all_tests gtest gtest_main)