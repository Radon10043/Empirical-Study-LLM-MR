from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test22(self, pattern: str, file: str):
        """Metamorphic Relation 22: If the word-regexp option is used, the output should only match the whole words and not partial matches."""
        # Get source output with word-regexp option
        process = os.popen(f"{GREP_PATH} -w -f {pattern} {file}")
        word_regexp_out = process.readlines()
        process.close()

        # Get source output without word-regexp option
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        normal_out = process.readlines()
        process.close()

        # Verification
        for line in normal_out:
            if line.strip():
                words = line.split()
                for word in words:
                    if pattern in word and line not in word_regexp_out:
                        self.fail("Partial match found when using word-regexp option")


if __name__ == "__main__":
    unittest.main()
