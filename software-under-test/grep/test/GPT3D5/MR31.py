from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test31(self, pattern: str, file: str):
        """Metamorphic Relation 31: If the '-i' option is used to ignore case distinctions, the output should be the same as when the pattern and input are both lowercased."""
        process_with_ignore_case = os.popen(f"{GREP_PATH} -i -f {pattern} {file}")
        output_with_ignore_case = process_with_ignore_case.readlines()
        process_with_ignore_case.close()

        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        follow_file = os.path.join(os.path.dirname(file), "follow_text.txt")
        with open(follow_pattern, "w") as ff:
            with open(pattern, "r") as sf:
                ff.write(sf.read().lower())
        with open(follow_file, "w") as ff:
            with open(file, "r") as sf:
                ff.write(sf.read().lower())

        process_lowercase = os.popen(f"{GREP_PATH} -f {follow_pattern} {follow_file}")
        output_lowercase = process_lowercase.readlines()
        process_lowercase.close()

        # Verification
        self.assertEqual(output_with_ignore_case, output_lowercase, "Output differs when using the -i option and lowercasing the pattern and input")


if __name__ == "__main__":
    unittest.main()
