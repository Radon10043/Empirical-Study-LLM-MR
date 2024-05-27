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
    def test22(self, vals: list):
        """Metamorphic Relation 22: If the Own_Tracked_Alt_Rate sign does not change (still climbing or descending), mild variations in the rate should not change the resolution advisory."""
        rate_variation = 100  # Example rate variation

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Create a list of rate variations to test
        rate_variations = [vals[INDEX["Own_Tracked_Alt_Rate"]] + rate_variation, vals[INDEX["Own_Tracked_Alt_Rate"]] - rate_variation]

        for variation in rate_variations:
            # Skip the variation if it would change the sign of the rate (to avoid changing from climb to descent or vice versa)
            if (variation < 0 and vals[INDEX["Own_Tracked_Alt_Rate"]] > 0) or (variation > 0 and vals[INDEX["Own_Tracked_Alt_Rate"]] < 0):
                continue

            # Construct follow-up input
            follow_vals = vals.copy()
            follow_vals[INDEX["Own_Tracked_Alt_Rate"]] = variation

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(source_out, follow_out, f"A change in Own_Tracked_Alt_Rate by {rate_variation} incorrectly altered the advisory.")


if __name__ == "__main__":
    unittest.main()
