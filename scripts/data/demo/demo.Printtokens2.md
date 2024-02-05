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