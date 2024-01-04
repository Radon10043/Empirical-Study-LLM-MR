# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of this program: There is a program whose input is three strings `A`, `B` and `C`, and it return a bool value representing whether `C` is the interleaving of `A` and `B`. Please identify the metamorphic relations of this program as much as possible and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code. Here is an example:

```cpp
/**
 * @brief Metamorphic Relation 1: Adding one same character to the end of A and C, the result will be the same.
 *
 */
TEST_P(InterleavingStringParamTest, MR1) {
    /* Get source input */
    InterleavingStringInput input = GetParam();
    string A = input.A, B = input.B, C = input.C;

    /* Get source output */
    bool source_out = is_interleaved(A, B, C);

    /* Construct follow-up input */
    char ch = 'a';
    string follow_A = A + ch, follow_C = C + ch;

    /* Get follow-up output */
    bool follow_out = is_interleaved(follow_A, B, follow_C);

    /* Verification */
    EXPECT_EQ(source_out, follow_out);
}
```

## Chat 4...n

Please identify more different metamorphic relations of this program and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code.