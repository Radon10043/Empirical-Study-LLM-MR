import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test19(self, pattern: str, file: str):
        """Metamorphic Relation 19: If the search pattern contains multiple expressions separated by OR logic, the output should contain lines matching any of the expressions."""
        # Get source output with original pattern
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct a follow-up input with an additional pattern separated by OR logic
        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        with open(follow_pattern, mode="w") as ff:
            with open(pattern, mode="r") as sf:
                ff.write(f"({sf.read()}|additional_pattern)")  # Example additional pattern

        # Get source output with follow-up pattern
        process = os.popen(f"{GREP_PATH} -f {follow_pattern} {file}")
        follow_up_out = process.readlines()
        process.close()

        # Verification
        tmp = str()
        with open(follow_pattern, mode="r") as f:
            tmp = f.read()
        for line in source_out:
            if line not in follow_up_out:
                self.assertTrue(any(content in line or "additional_pattern" in line for content in tmp.split('|')))  # Ensure the line matches at least one pattern in the follow-up expression


if __name__ == "__main__":
    unittest.main()
