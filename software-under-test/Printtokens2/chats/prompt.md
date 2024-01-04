# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of the program `print_tokens2`. `print_tokens2` is a lexical analyzer from Simens programs. Its input is a sequence of strings, and its outputs are all the tokens and their categories in order. Please identify the metamorphic relations of `print_tokens2` as much as possible and codify them as Python code. Here are some examples:

```python
@parameterized.expand(load_test_cases)
def test1(self, tc: str):
    """Metamorphic Relation 1: Adding a new line that only includes a comma, the follow-up output's rows equals the source output's rows plus one."""
    # Get source output
    source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

    # Construct follow-up input
    follow_tc = tc + "\n,"

    # Get follow-up output
    follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

    # Verification
    self.assertEqual(len(source_out) + 1, len(follow_out))

@parameterized.expand(load_test_cases)
def test2(self, tc: str):
    """Metamorphic Relation 2: Deleting the comments, the output should not change"""
    # Get source output
    source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

    # Construct follow-up input
    follow_tc = tc.split("\n")
    for i in range(len(follow_tc)):
        follow_tc[i] = follow_tc[i].split(";")[0]
    follow_tc = "\n".join(follow_tc)

    # Get follow-up output
    follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

    # Verification
    self.assertEqual(source_out, follow_out)

@parameterized.expand(load_test_cases)
def test3(self, tc: str):
    """Metamorphic Relation 3: Adding the comment, the output should not change"""
    # Get source output
    source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

    # Construct follow-up input
    follow_tc = tc + "; Comment!\n"

    # Get follow-up output
    follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

    # Verification
    self.assertEqual(source_out, follow_out)
```

## Chat 4...n

Please identify more different metamorphic relations of this program and codify them as Python code.