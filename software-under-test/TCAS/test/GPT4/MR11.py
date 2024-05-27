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
    def test11(self, vals: list):
        """Metamorphic Relation 11: Switching the Own_Tracked_Alt_Rate and Other_Tracked_Alt while keeping all other parameters the same should not change the advisory if Own_Tracked_Alt and Other_Tracked_Alt are considerably far from each other."""
        # Assuming a considerable distance to be at least 1000 feet.
        if abs(vals[INDEX["Own_Tracked_Alt"]] - vals[INDEX["Other_Tracked_Alt"]]) < 1000:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Own_Tracked_Alt_Rate"]] = vals[INDEX["Other_Tracked_Alt"]]

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
