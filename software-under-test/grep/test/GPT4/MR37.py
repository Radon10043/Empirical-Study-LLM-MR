import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test37(self, pattern: str, file: str):
        """Metamorphic Relation 37: Searching with '--mmap' should yield the same matches as without it.
        Note: '--mmap' is a less common option that tells grep to use memory-mapped input if possible.
        """
        # Normal search
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        normal_matches = int(process.read().strip())
        process.close()

        # Search with '--mmap'
        process = os.popen(f"{GREP_PATH} --mmap -c {pattern} {file}")
        mmap_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(normal_matches, mmap_matches)


if __name__ == "__main__":
    unittest.main()
