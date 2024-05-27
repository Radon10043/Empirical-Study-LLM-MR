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
    def test17(self, vals: list):
        """Metamorphic Relation 17: If the other aircraft's altitude remains unchanged, changing only the rate of descent or climb of the own aircraft should not change the resolution advisory from descending to climbing or vice versa."""
        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()
        original_advisory = source_out

        # Vary the rate of climb/descent of the own aircraft
        rate_changes = [-500, 500]  # Assume testing climb/descent rate adjustments by 500 feet/min

        for rate_change in rate_changes:
            # Construct follow-up input with adjusted climb/descent rate
            follow_vals = vals.copy()
            follow_vals[INDEX["Own_Tracked_Alt_Rate"]] += rate_change

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()
            follow_advisory = follow_out

            # Verification
            if (original_advisory == "1" and follow_advisory == "2") or (original_advisory == "2" and follow_advisory == "1"):
                self.fail("Advisory incorrectly switched between climbing and descending.")


if __name__ == "__main__":
    unittest.main()
