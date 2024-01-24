from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test23(self, vals: list):
        """Metamorphic Relation 23: If the Up_Separation is less than the Down_Separation, and high confidence is set to 1, and both reports are valid, then the output should not change when Other_RAC is changed."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Up_Separation"]] < vals[INDEX["Down_Separation"]] and vals[INDEX["High_Confidence"]] == 1 and vals[INDEX["Two_of_Three_Reports_Valid"]] == 1:
            follow_vals[INDEX["Other_RAC"]] = (follow_vals[INDEX["Other_RAC"]] + 1) % len(OTHER_RAC_VALUES)  # Change Other_RAC

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
