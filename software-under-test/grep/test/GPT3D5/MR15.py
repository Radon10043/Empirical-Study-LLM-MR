from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test15(self, pattern: str, file: str):
        """Metamorphic Relation 15: If the regular expression pattern is negated, the output should contain lines that do not match the negated pattern."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input with negated pattern
        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        with open(follow_pattern, mode="w") as ff:
            with open(pattern) as sf:
                ff.write(f"^(?!.*{sf.read()}).*$")
        process = os.popen(f"{GREP_PATH} -f {follow_pattern} {file}")
        follow_up_out = process.readlines()
        process.close()

        # Verification
        self.assertTrue(set(follow_up_out).issubset(set(source_out)))


if __name__ == "__main__":
    unittest.main()
