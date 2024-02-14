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
    def test24(self, vals: list):
        """Metamorphic Relation 24: If the separation thresholds are adjusted, the advisory should remain the same if the Cur_Vertical_Separation is halved."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Separation_Thresholds"]] += 100  # Adjusting the separation thresholds
        follow_vals[INDEX["Cur_Vertical_Sep"]] = vals[INDEX["Cur_Vertical_Sep"]] / 2  # Halving the Cur_Vertical_Sep

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
