add_executable(exampleTest tmain.cpp exampleTest.cpp utils.cpp utils.h ../src/function.h)
target_link_libraries(exampleTest PRIVATE gtest)
target_link_libraries(exampleTest PRIVATE pthread)

add_executable(GPT3D5Test tmain.cpp GPT3D5Test.cpp utils.cpp utils.h ../src/function.h)
target_link_libraries(GPT3D5Test PRIVATE gtest)
target_link_libraries(GPT3D5Test PRIVATE pthread)

add_executable(GPT4Test tmain.cpp GPT4Test.cpp utils.cpp utils.h ../src/function.h)
target_link_libraries(GPT4Test PRIVATE gtest)
target_link_libraries(GPT4Test PRIVATE pthread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_test(NAME exampleTest COMMAND exampleTest)
add_test(NAME GPT3D5Test COMMAND GPT3D5Test)
add_test(NAME GPT4Test COMMAND GPT4Test)