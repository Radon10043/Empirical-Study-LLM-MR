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
    def test20(self, vals: list):
        """Metamorphic Relation 20: If the Other_Tracked_Alt parameter is adjusted based on the relationship with Own_Tracked_Alt, the output should change accordingly."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Other_Tracked_Alt"]] = 2 * follow_vals[INDEX["Own_Tracked_Alt"]]  # Adjusting the Other_Tracked_Alt based on the relationship with Own_Tracked_Alt

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
