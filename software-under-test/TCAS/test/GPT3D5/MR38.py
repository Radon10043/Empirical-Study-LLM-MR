from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test38(self, vals: list):
        """Metamorphic Relation 38: If the Cur_Vertical_Sep and Own_Tracked_Alt values are unchanged and the Other_Tracked_Alt values are doubled, the output should change accordingly."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Other_Tracked_Alt"]] *= 2  # Doubling the Other_Tracked_Alt values

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
