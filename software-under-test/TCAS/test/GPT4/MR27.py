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
    def test27(self, vals: list):
        """Metamorphic Relation 27: Increasing both 'Up_Separation' and 'Down_Separation' beyond their original values should not provide an advisory to decrease altitude."""
        # Increase both 'Up_Separation' and 'Down_Separation' beyond their original values
        separation_increase = 1000

        # Ensure the separation values do not surpass the potential system limits before applying the increase
        if vals[INDEX["Up_Separation"]] + separation_increase > 99000 or vals[INDEX["Down_Separation"]] + separation_increase > 99000:
            return

        follow_vals = vals.copy()
        follow_vals[INDEX["Up_Separation"]] += separation_increase
        follow_vals[INDEX["Down_Separation"]] += separation_increase

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        if follow_out == "2":  # DOWNWARD_RA should not be the advisory after increasing separations
            self.fail("Increasing separations incorrectly resulted in a DOWNWARD_RA advisory.")


if __name__ == "__main__":
    unittest.main()
