import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test14(self, pattern: str, file: str):
        """Metamorphic Relation 14: A pattern search within a file versus within the file
        piped from 'cat' should yield the same results.
        """
        # Get source output by searching within the file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Get follow-up output by piping the file content to grep
        process = os.popen(f"cat {file} | {GREP_PATH} -c {pattern}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
