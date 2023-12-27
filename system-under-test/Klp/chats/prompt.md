# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the system under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the system under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

# Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of this system: There is a function that implements the KLP algorithm. Given a matrix `M`, `M[i][j]=1` indicates that the ith key can open the jth lock, and 0 otherwise. Its input is a matrix, which stores the relation between keys and locks. Its output is an array representing the smallest set of keys that can open all locks. Please identify the metamorphic relation of this function as much as possible and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code. Here are some examples:

```C++
/**
 * @brief Metamorphic relation 1: Adding a useless key row (all 0s, these cannot open any lock)
 * to the end of the matrix, then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR1) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    follow_matrix.push_back(vector<int>(follow_matrix[0].size()));

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}

/**
 * @brief Metamorphic Relation 2: Adding a column with all 1s (the added lock can be opened by any key)
 * to the matrix, then the output will not change.
 *
 */
TEST_P(KLPParamTest, MR2) {
    /* Get source input */
    KLPInput input = GetParam();
    vector<vector<int>> matrix = input.matrix;

    /* Get source output */
    vector<int> source_out = KLP(matrix);

    /* Construct follow-up input */
    vector<vector<int>> follow_matrix = matrix;
    for (auto &row : follow_matrix)
        row.emplace_back(1);

    /* Get follow-up output */
    vector<int> follow_out = KLP(follow_matrix);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
```

# Chat 4...n

Please identify more different metamorphic relations of this system.