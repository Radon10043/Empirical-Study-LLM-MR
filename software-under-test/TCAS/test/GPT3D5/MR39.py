import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
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
    def test39(self, vals: list):
        """Metamorphic Relation 39: If the Own_Tracked_Alt, Other_Tracked_Alt and Cur_Vertical_Sep parameters are preserved and the High_Confidence flag is toggled, the advisories provided by the TCAS should remain unchanged."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["High_Confidence"]] = not follow_vals[INDEX["High_Confidence"]]  # Toggling the High_Confidence flag

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
