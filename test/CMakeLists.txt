
set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp)
target_link_libraries(test filter gtest)
add_test(test test)