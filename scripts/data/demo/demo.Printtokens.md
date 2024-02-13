```python
@parameterized.expand(load_test_cases(1000))
def test1(self, tc: str):
    """Metamorphic Relation 1: Changing all the characters from lower case to upper case, the keyword will disappear."""
    # Get source output
    source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

    # Construct follow-up input
    follow_tc = tc.upper()

    # Get follow-up output
    follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

    # Verification
    type_list = list()
    for line in follow_out:
        type_list.append(line.split(",")[0])
    self.assertNotIn("keyword", type_list)

@parameterized.expand(load_test_cases)
def test2(self, tc: str):
    """Metamorphic Relation 2: Deleting the comments, the output should not change"""
    # Get source output
    source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

    # Construct follow-up input
    follow_tc = tc.split("\n")
    for i in range(len(follow_tc)):
        follow_tc[i] = follow_tc[i].split(";")[0]
    follow_tc = "\n".join(follow_tc)

    # Get follow-up output
    follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

    # Verification
    self.assertEqual(source_out, follow_out)

@parameterized.expand(load_test_cases)
def test3(self, tc: str):
    """Metamorphic Relation 3: Adding the comment, the output should not change"""
    # Get source output
    source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

    # Construct follow-up input
    follow_tc = tc + "; Comment!"

    # Get follow-up output
    follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

    # Verification
    self.assertEqual(source_out, follow_out)
```