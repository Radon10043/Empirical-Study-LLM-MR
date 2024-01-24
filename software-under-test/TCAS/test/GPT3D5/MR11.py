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
    def test11(self, vals: list):
        """Metamorphic Relation 11: If the altitudes are reversed (Own_Tracked_Alt becomes Other_Tracked_Alt and vice versa), the output should remain the same."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Own_Tracked_Alt"]], follow_vals[INDEX["Other_Tracked_Alt"]] = follow_vals[INDEX["Other_Tracked_Alt"]], follow_vals[INDEX["Own_Tracked_Alt"]]  # Reverse altitudes

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
