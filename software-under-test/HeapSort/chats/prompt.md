# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of this program: There is a program that implements heap sort for input array. Its input is an integer array, and its return value is an array sorted in descending order. Please identify the metamorphic relations of this program as much as possible and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code. Here are some examples:

```cpp
/**
 * @brief Metamorphic relation 1: Shuffling the elements in the input array, the output will be the same.
 *
 */
TEST_P(HeapSortParamTest, MR1) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    shuffle(follow_vec.begin(), follow_vec.end(), random_device());

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 2: Adding a constant to each element in the input array, then each element of the output array will be larger by the constant
 * than the element at the same location of the source input.
 *
 */
TEST_P(HeapSortParamTest, MR2) {
    int constant = 3;

    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem += constant;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem -= constant;
    EXPECT_EQ(follow_out, source_out);
}

/**
 * @brief Metamorphic Relation 3: Multiplying -1 to each element in the input array, then if we multiply -1 to each element of the output array, it should be
 * the same as the source output array, but in reverse order.
 *
 */
TEST_P(HeapSortParamTest, MR3) {
    /* Get source input */
    HeapSortInput input = GetParam();
    vector<int> source_vec = input.vec;

    /* Get source output */
    vector<int> source_out = heap_sort(source_vec);

    /* Construct follow-up input */
    vector<int> follow_vec = source_vec;
    for (auto &elem : follow_vec)
        elem *= -1;

    /* Get follow-up output */
    vector<int> follow_out = heap_sort(follow_vec);

    /* Verification */
    for (auto &elem : follow_out)
        elem *= -1;
    reverse(follow_out.begin(), follow_out.end());
    EXPECT_EQ(follow_out, source_out);
}
```

## Chat 4...n

Please identify more different metamorphic relations of this program and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code.