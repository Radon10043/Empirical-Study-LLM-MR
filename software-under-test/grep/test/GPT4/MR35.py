import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test35(self, pattern: str, file: str):
        """Metamorphic Relation 35: Running 'grep' with a pattern on a symlink to a file should yield
        the same matches as running 'grep' on the original file.
        """
        # Get output from the original file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        # Create a symlink to the original file
        symlink = f"{file}_symlink"
        os.symlink(file, symlink)

        # Get output from the symlink
        process = os.popen(f"{GREP_PATH} -c {pattern} {symlink}")
        symlink_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(original_matches, symlink_matches)
        os.remove(symlink)


if __name__ == "__main__":
    unittest.main()
