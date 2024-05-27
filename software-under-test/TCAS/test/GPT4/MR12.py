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
    def test12(self, vals: list):
        """Metamorphic Relation 12: Changing the Alt_Layer_Value should not alter the advisory if there is no altitude limit affecting the current scenario."""
        # Assuming altitude layers affect advisories when altitude rates are significant.
        if vals[INDEX["Own_Tracked_Alt_Rate"]] > 100 or vals[INDEX["Own_Tracked_Alt_Rate"]] < -100:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Alt_Layer_Value"]] = (follow_vals[INDEX["Alt_Layer_Value"]] + 1) % 4  # Assuming there are 4 altitude layers.

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
