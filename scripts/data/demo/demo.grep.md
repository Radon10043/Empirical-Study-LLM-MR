```python
@parameterized.expand(load_test_cases)
def test1(self, pattern: str, file: str):
    """Metamorphic Relation 1: If a character is added to the end of the search term,
    the length of the output length should be the same as or less than the original.
    """
    # Get source output
    process = os.popen(f"{GREP_PATH} {pattern} {file}")
    source_out = process.readlines()
    process.close()

    # Construct follow-up input
    follow_pattern = pattern + "a"

    # Get follow-up output
    process = os.popen(f"{GREP_PATH} {follow_pattern} {file}")
    follow_out = process.readlines()
    process.close()

    # Verification
    self.assertLessEqual(len(follow_out), len(source_out))

@parameterized.expand(load_test_cases)
def test2(self, pattern: str, file: str):
    """Metamorphic Relation 2: If case distinctions are ignored, swap the case of search term,
    the output should be the same.
    """
    # Get source output
    process = os.popen(f"{GREP_PATH} --ignore-case {pattern} {file}")
    source_out = process.readlines()
    process.close()

    # Construct follow-up input
    follow_pattern = pattern.swapcase()

    # Get follow-up output
    process = os.popen(f"{GREP_PATH} --ignore-case {follow_pattern} {file}")
    follow_out = process.readlines()
    process.close()

    # Verification
    self.assertEqual(source_out, follow_out)

@parameterized.expand(load_test_cases)
def test3(self, pattern, file):
    """Metamorphic Relation 3: If regular expression matching is enabled, add an asterisk at
    the end of the search term, the output should be the same.
    """
    # Get source output
    process = os.popen(f'{GREP_PATH} --regexp="{pattern}" {file}')
    source_out = process.readlines()
    process.close()

    # Construct follow-up input
    follow_pattern = f"{pattern}*"

    # Get follow-up output
    process = os.popen(f'{GREP_PATH} --regexp="{follow_pattern}" {file}')
    follow_out = process.readlines()
    process.close()

    # Verification
    self.assertEqual(source_out, follow_out)
```