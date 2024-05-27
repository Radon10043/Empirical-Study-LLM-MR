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
    def test10(self, vals: list):
        """Metamorphic Relation 10: If 'Climb_Inhibit' is set, the advice to climb should not be given when Other_RAC is DO_NOT_CLIMB."""
        if vals[INDEX["Other_RAC"]] != OTHER_RAC_VALUES["DO_NOT_CLIMB"]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Climb_Inhibit"]] = 1

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        if follow_out == "1":  # UPWARD_RA should not happen when climb is inhibited.
            self.fail("Climb inhibit did not prevent UPWARD_RA when Other_RAC is DO_NOT_CLIMB.")
        else:
            # The actual assertion for metamorphic testing is not necessary for this case.
            pass


if __name__ == "__main__":
    unittest.main()
