add_executable(exampleTest tmain.cpp exampleTest.cpp utils.cpp utils.h ../src/function.h)
target_link_libraries(exampleTest PRIVATE gtest)
target_link_libraries(exampleTest PRIVATE pthread)

add_executable(GPT3D5Test tmain.cpp GPT3D5Test.cpp utils.cpp utils.h ../src/function.h)
target_link_libraries(GPT3D5Test PRIVATE gtest)
target_link_libraries(GPT3D5Test PRIVATE pthread)

set_property(TARGET GPT3D5Test PROPERTY CXX_STANDARD 17)
set_property(TARGET GPT3D5Test PROPERTY CXX_STANDARD_REQUIRED ON)

add_test(NAME exampleTest COMMAND exampleTest)
add_test(NAME GPT3D5Test COMMAND GPT3D5Test)