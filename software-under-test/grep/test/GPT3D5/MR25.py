from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test25(self, pattern: str, file: str):
        """Metamorphic Relation 25: If the fixed strings option is used with multiple fixed strings, the output should be the same as when searching each fixed string separately."""
        with open(pattern, mode="r+") as f:
            ori = f.read()
            f.write(ori + "\na")

        # Get source output with the fixed strings option
        process = os.popen(f"{GREP_PATH} -F -f {pattern} {file}")
        fixed_strings_out = process.readlines()
        process.close()

        # Get source output when searching each fixed string separately
        individual_strings_out = []
        with open(pattern) as f:
            for line in f.readlines():
                line = line.rstrip("\n")
                process = os.popen(f"{GREP_PATH} -F {line} {file}")
                individual_strings_out.extend(process.readlines())
                process.close()

        # Verification
        self.assertEqual(set(fixed_strings_out), set(individual_strings_out))


if __name__ == "__main__":
    unittest.main()
