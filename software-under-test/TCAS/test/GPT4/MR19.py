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
    def test19(self, vals: list):
        """Metamorphic Relation 19: Switching the intention of the other aircraft between climb and descend should reverse the resolution advisory between UPWARD_RA and DOWNWARD_RA, if other factors remain conducive for an RA."""
        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Skip the test if the source did not result in a climb or descend advisory
        if source_out not in ("1", "2"):  # Corresponds to UPWARD_RA or DOWNWARD_RA advisories
            return

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_CLIMB"]:
            follow_vals[INDEX["Other_RAC"]] = OTHER_RAC_VALUES["DO_NOT_DESCEND"]
        elif vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_DESCEND"]:
            follow_vals[INDEX["Other_RAC"]] = OTHER_RAC_VALUES["DO_NOT_CLIMB"]
        else:
            # If other RAC is NO_INTENT, no change in the opposite advisory can be inferred, so skip test
            return

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification - Expect the opposite advisory
        expected_follow_out = "1" if source_out == "2" else "2"
        self.assertEqual(follow_out, expected_follow_out, "Switching between DO_NOT_CLIMB and DO_NOT_DESCEND did not reverse the advisory.")


if __name__ == "__main__":
    unittest.main()
