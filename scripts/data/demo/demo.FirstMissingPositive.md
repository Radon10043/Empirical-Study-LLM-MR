```c++
/**
 * @brief Metamorphic Relation 1: Adding one integer to the source array, which is identical to
 * one element of the original array, the output should be the same.
 *
 */
TEST_P(FMPInputParamTest, MR1) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    follow_vec.push_back(source_vec.front());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 2: Shuffling the elements in the input array, the output will be the same.
 *
 */
TEST_P(FMPInputParamTest, MR2) {
    /* Get source input */
    FMPInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    int source_out = first_missing_positive(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    shuffle(follow_vec.begin(), follow_vec.end(), random_device());

    /* Get follow-up output */
    int follow_out = first_missing_positive(follow_vec);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
```