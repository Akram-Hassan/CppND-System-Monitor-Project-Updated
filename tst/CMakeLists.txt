include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(TEST_BINARY ${CMAKE_PROJECT_NAME}_tst)

list(REMOVE_ITEM SOURCES ${SOURCE_DIR}/main.cpp)
list(REMOVE_ITEM SOURCES ${SOURCE_DIR}/ncurses_display.cpp)

file(GLOB TEST_SOURCES "*.cpp")


add_executable(
    ${TEST_BINARY}
    ${SOURCES}
    ${TEST_SOURCES}
) 

target_link_libraries(
    ${TEST_BINARY}
    GTest::gtest_main
)

# add_test(NAME monitor_tests COMMAND ${TEST_BINARY})

include(GoogleTest)
gtest_discover_tests(${TEST_BINARY})




