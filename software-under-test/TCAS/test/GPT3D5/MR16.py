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
    def test16(self, vals: list):
        """Metamorphic Relation 16: If the Up_Separation is greater than the Down_Separation, and the high confidence is set to 1, then changing the value of Other_RAC should not change the output."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["High_Confidence"]] = 1
        if vals[INDEX["Up_Separation"]] > vals[INDEX["Down_Separation"]]:
            follow_vals[INDEX["Other_RAC"]] = (follow_vals[INDEX["Other_RAC"]] + 1) % len(OTHER_RAC_VALUES)  # Change Other_RAC

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
