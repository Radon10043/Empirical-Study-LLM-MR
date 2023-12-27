add_executable(exampleTest tmain.cpp exampleTest.cpp ../src/function.h)
target_link_libraries(exampleTest PRIVATE gtest)
target_link_libraries(exampleTest PRIVATE pthread)

add_executable(GPTTest tmain.cpp GPTTest.cpp ../src/function.h)
target_link_libraries(GPTTest PRIVATE gtest)
target_link_libraries(GPTTest PRIVATE pthread)

add_test(NAME exampleTest COMMAND exampleTest)
add_test(NAME GPTTest COMMAND GPTTest)