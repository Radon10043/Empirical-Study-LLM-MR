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
    def test14(self, vals: list):
        """Metamorphic Relation 14: If Own_Tracked_Alt is greater than Other_Tracked_Alt, and the vertical separation is constant, the output should not change."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Own_Tracked_Alt"]] = vals[INDEX["Other_Tracked_Alt"]] + 1000  # Set Own_Tracked_Alt greater than Other_Tracked_Alt

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
