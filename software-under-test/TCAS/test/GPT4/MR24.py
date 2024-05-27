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
    def test24(self, vals: list):
        """Metamorphic Relation 24: If the Other_RAC is NO_INTENT and the Own_Tracked_Alt and Other_Tracked_Alt are swapped without changing their relative distance, the resolution advisory should remain unchanged."""
        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        if vals[INDEX["Other_RAC"]] != OTHER_RAC_VALUES["NO_INTENT"]:
            return

        relative_distance = abs(vals[INDEX["Own_Tracked_Alt"]] - vals[INDEX["Other_Tracked_Alt"]])

        # Construct follow-up input: Swap altitudes maintaining relative distance
        follow_vals = vals.copy()
        if vals[INDEX["Own_Tracked_Alt"]] > vals[INDEX["Other_Tracked_Alt"]]:
            follow_vals[INDEX["Own_Tracked_Alt"]] = vals[INDEX["Other_Tracked_Alt"]]
            follow_vals[INDEX["Other_Tracked_Alt"]] = vals[INDEX["Other_Tracked_Alt"]] + relative_distance
        else:
            follow_vals[INDEX["Other_Tracked_Alt"]] = vals[INDEX["Own_Tracked_Alt"]]
            follow_vals[INDEX["Own_Tracked_Alt"]] = vals[INDEX["Own_Tracked_Alt"]] + relative_distance

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        self.assertEqual(source_out, follow_out, "Swapping Own_Tracked_Alt and Other_Tracked_Alt while preserving relative distance changed the output against the metamorphic relation.")


if __name__ == "__main__":
    unittest.main()
