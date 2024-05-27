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
    def test32(self, vals: list):
        """Metamorphic Relation 32: A significant increase in the other aircraft's altitude should not result in an upward resolution advisory if the Own_Tracked_Alt remains constant."""
        altitude_increase = 1000  # Arbitrary significant altitude increase for the other aircraft

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Construct follow-up input with increased Other_Tracked_Alt
        follow_vals = vals.copy()
        follow_vals[INDEX["Other_Tracked_Alt"]] += altitude_increase

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        if follow_out == "1":  # UPWARD_RA should not be advised if only the other aircraft increased altitude
            self.fail("Significant increase in the other aircraft's altitude resulted in an incorrect upward advisory.")


if __name__ == "__main__":
    unittest.main()
