add_executable(exampleTest tmain.cpp exampleTest.cpp ../src/function.h)
target_link_libraries(exampleTest PRIVATE gtest)
target_link_libraries(exampleTest PRIVATE pthread)

add_executable(GPT3P5Test tmain.cpp GPT3P5Test.cpp ../src/function.h)
target_link_libraries(GPT3P5Test PRIVATE gtest)
target_link_libraries(GPT3P5Test PRIVATE pthread)

add_executable(GPT4Test tmain.cpp GPT4Test.cpp ../src/function.h)
target_link_libraries(GPT4Test PRIVATE gtest)
target_link_libraries(GPT4Test PRIVATE pthread)

add_test(NAME exampleTest COMMAND exampleTest)
add_test(NAME GPT3P5Test COMMAND GPT3P5Test)
add_test(NAME GPT4Test COMMAND GPT4Test)