# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the system under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the system under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

# Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of this system: There is a function that implements the binary search algorithm to find the occurrence index of the specific element in the ascending array. Its inputs are 2 variables: `vec` and `target`, representing an ascending array and the element to be searched, respectively. Its return value is an integer representing the occurrence index of `target` in `vec`. If `target`does not occur in `vec`, the function returns -1. Please identify the metamorphic relation of this function as much as possible and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code. Here are some examples:

```C++
/**
 * @brief Metamorphic relation 1: Add an element to the end of the array and keep the array in
 * ascending order, the output should be unchanged or greater.
 *
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, target);

    /* Verification */
    EXPECT_LE(source_out, follow_out);
}

/**
 * @brief Metamorphic relation 2: Multiply all elements in the array and the element to be located by a constant,
 * the output should remain the same.
 *
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get source input */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get source output */
    int source_out = bin_search(vec, target);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int &val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = bin_search(follow_vec, follow_target);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
```

# Chat 4...n

Please identify more different metamorphic relations of this system.