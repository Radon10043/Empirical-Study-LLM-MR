# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of this program: There is a program that captures all regions surrounded by 'X', and all 'O's in these regions will be flipped into 'X's. Its input is a two-dim board containing 'X's and 'O's. We use a string array to represent this two-dim board. Its output is also a string array, but all 'O's in regions surrounded by 'X' is flipped to 'X's. Please identify the metamorphic relations of this program as much as possible and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code. Here are some examples:

```cpp
/**
 * @brief Metamorphic Relation 1: Adding one row with all 'O's to the end of the matrix, then the output should be ncreased by one row with all 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR1) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    int cols = source_vec[0].length();
    vector<string> follow_vec = source_vec;
    follow_vec.push_back(string(cols, 'O'));

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    source_out.push_back(string(cols, 'O'));
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Adding one column with all 'O's to the end of the matrix , then the output should be increased by one column with all 'O's.
 *
 */
TEST_P(SurroundedRegionParamTest, MR2) {
    /* Get source input */
    SurroundedRegionInput input = GetParam();
    vector<string> source_vec = input.vec;

    /* Get source output */
    vector<string> source_out = surrounded_region(source_vec);

    /* Construct follow-up input */
    vector<string> follow_vec = source_vec;
    for (auto& row : follow_vec) row.push_back('O');

    /* Get follow-up output */
    vector<string> follow_out = surrounded_region(follow_vec);

    /* Verification */
    for (auto& row : source_out) row.push_back('O');
    EXPECT_EQ(follow_out, source_out);
}
```

## Chat 4...n

Please identify more different metamorphic relations of this program and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code.