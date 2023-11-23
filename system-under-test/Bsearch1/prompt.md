# Chat 1

Assume there is a trigonometric function sin(x), a source input x1, and a corresponding source output y1. If follow-up input x2=pi-x1 and corresponding follow-up output y2=y1, we say there is a metamorphic relation sin(x)=sin(pi-x).

Next, you need to identify the metamorphic relation of a function. There is a function that implements the binary search algorithm to find the occurrence index of the specific element in the ascending array. Its inputs are 2 variables: ```vec``` and ```target```, representing an ascending array and the element to be searched, respectively. Its return value is an integer representing the occurrence index of ```target``` in ```vec```. If ```target```does not occur in ```vec```, the function returns -1. Please identify the metamorphic relation of this function as much as possible and use Google's C++ testing and mocking framework ```googletest``` to codify them as C++ code.

Here is some examples:

```C++
/**
 * Metamorphic relation 1: Add an element to the end of the array and keep the array in
 * ascending order, the output should be unchanged or greater.
 */
TEST_P(BSearchParamTest, MR1) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    vector<int> follow_vec = vec;
    follow_vec.emplace_back(vec.back() + 1);

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_LE(origin_out, follow_out);
}

/**
 * Metamorphic relation 2: Multiply all elements in the array and the element to be located by a constant,
 * the output should remain the same.
 */
TEST_P(BSearchParamTest, MR2) {
    /* Get input data */
    BSearch1Input input = GetParam();
    vector<int> vec = input.vec;
    int target = input.target;

    /* Get origin output */
    int origin_out = BinSearch(vec, target, 0, vec.size() - 1);

    /* Construct follow-up input */
    int constant = 2;
    vector<int> follow_vec = vec;
    for (int& val : follow_vec)
        val *= constant;
    int follow_target = target * constant;

    /* Get follow-up output */
    int follow_out = BinSearch(follow_vec, follow_target, 0, follow_vec.size() - 1);

    /* Verification */
    EXPECT_EQ(origin_out, follow_out);
}
```

# Chat 2

Please generate more different metamorphic relations.