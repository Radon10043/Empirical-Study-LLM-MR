from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test4(self, pattern: str, file: str):
        """Metamorphic Relation 4: If the invert match option is used, the output should be complementary to the original output."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Get invert match output
        process = os.popen(f"{GREP_PATH} -v -f {pattern} {file}")
        invert_out = process.readlines()
        process.close()

        # Verification
        self.assertTrue(set(source_out).isdisjoint(set(invert_out)))


if __name__ == "__main__":
    unittest.main()
