# Chat 1

Assume there is a trigonometric function sin(x), a source input x1, and a corresponding source output y1. If follow-up input x2=pi-x1 and corresponding follow-up output y2=y1, we say there is a metamorphic relation sin(x)=sin(pi-x).

Next, you need to identify the metamorphic relation of the function `p`. The specification of this function is as follows:

- The function implements the binary search algorithm to determine whether the specific element occurs in the ascending array.
- The function's input is 2 variables: `vec` and `target`, representing an ascending array and the element to be searched, respectively.
- The function's return value is an integer representing whether `target` occurs in `vec`. If `target` does not occur in `vec`, the function returns 0; otherwise returns 1.
- If elements in `vec` are changed, `vec` must also remain in ascending order.

Please identify the metamorphic relation of this function as much as possible and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code.

Here are some examples:

```C++
/**
 * Metamorphic relation 1: If the target value is already in the array, add an element greater than the max value in array to the end of the array, and the output should be unchanged.
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    if (!origin_out) return;

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = p(follow_vec, target, follow_vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}

/**
 * Metamorphic relation 2: Multiply all elements in the array and the element to be located by a constant, the output should remain the same.
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get input data */
    BSearch2Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = p(vec, target, vec.size());

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = p(follow_vec, follow_target, follow_vec.size());

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}
```

# Chat 2

Please generate more different metamorphic relations.