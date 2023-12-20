set(CMAKE_CXX_STANDARD 17)

add_executable(exampleTest tmain.cpp exampleTest.cpp ../src/function.h)
target_link_libraries(exampleTest PRIVATE gtest)
target_link_libraries(exampleTest PRIVATE pthread)

add_test(NAME exampleTest COMMAND exampleTest)