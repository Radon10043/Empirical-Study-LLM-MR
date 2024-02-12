from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test2(self, pattern: str, file: str):
        """Metamorphic Relation 2: If case distinctions are ignored, swap the case of search term,
        the output should be the same.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} --ignore-case -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        with open(follow_pattern, mode="w") as ff:
            with open(pattern) as sf:
                ff.write(sf.read().swapcase())

        # Get follow-up output
        process = os.popen(f"{GREP_PATH} --ignore-case -f {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
