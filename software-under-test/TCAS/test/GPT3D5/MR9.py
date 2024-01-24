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
    def test9(self, vals: list):
        """Metamorphic Relation 9: If the altitude of own aircraft is increased, and the altitude of the other tracked aircraft is decreased by the same amount, the output should remain the same."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        increase_altitude = 1000  # Increase altitude by 1000 (or any other suitable amount)
        follow_vals[INDEX["Own_Tracked_Alt"]] += increase_altitude
        follow_vals[INDEX["Other_Tracked_Alt"]] -= increase_altitude

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
