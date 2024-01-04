# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of this program: There is a program that implements RSA encryption. Its input is four integers: `m`, `e`, `p`, and `q`. Its output value is a long integer representing the number that RSA encrypts. Please identify the metamorphic relations of this program as much as possible and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code. Here is an example:

```cpp
/**
 * @brief Metamorphic Relation 1: Keeping p, q and e the same, giving a new plaintext which is equals to m + p*q, the ciphertext is the same.
 *
 */
TEST_P(RSAParamTest, MR1) {
    /* Get source input */
    RSAInput input = GetParam();
    int source_m = input.m, source_e = input.e, source_p = input.p, source_q = input.q;

    /* Get source output */
    long long source_out = candp(source_m, source_e, source_p, source_q);

    /* Construct follow-up input */
    int follow_m = source_m + source_p * source_q;

    /* Get follow-up output */
    long long follow_out = candp(follow_m, source_e, source_p, source_q);

    /* Verification */
    ASSERT_EQ(source_out, follow_out);
}
```

## Chat 4...n

Please identify more different metamorphic relations of this program and use Google's C++ testing and mocking framework `googletest` to codify them as C++ code.