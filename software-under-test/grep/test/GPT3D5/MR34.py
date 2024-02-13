from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test34(self, pattern: str, file: str):
        """Metamorphic Relation 34: If the pattern is enclosed in quotes, the output should be the same as when using the pattern without quotes."""
        process_with_quotes = os.popen(f'{GREP_PATH} -f "{pattern}" {file}')
        output_with_quotes = process_with_quotes.readlines()
        process_with_quotes.close()

        process_without_quotes = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_quotes = process_without_quotes.readlines()
        process_without_quotes.close()

        # Verification
        self.assertEqual(output_with_quotes, output_without_quotes, "Output differs when using quotes around the pattern")


if __name__ == "__main__":
    unittest.main()
