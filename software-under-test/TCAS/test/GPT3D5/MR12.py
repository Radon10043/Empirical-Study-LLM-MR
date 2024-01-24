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
    def test12(self, vals: list):
        """Metamorphic Relation 12: If the own altitude rate is negative, and the other altitude rate is positive, the output should not change."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Own_Tracked_Alt_Rate"]] = -abs(follow_vals[INDEX["Own_Tracked_Alt_Rate"]])  # Set own rate negative
        follow_vals[INDEX["Other_Tracked_Alt_Rate"]] = abs(follow_vals[INDEX["Other_Tracked_Alt_Rate"]])  # Set other rate positive

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
