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
    def test7(self, vals: list):
        """Metamorphic Relation 7: Reversing the climb or descend intention of the other aircraft should not change the advisory result if 'Other_Capability' suggests it is not TCAS equipped."""
        if vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["TCAS_TA"]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        if follow_vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_CLIMB"]:
            follow_vals[INDEX["Other_RAC"]] = OTHER_RAC_VALUES["DO_NOT_DESCEND"]
        elif follow_vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_DESCEND"]:
            follow_vals[INDEX["Other_RAC"]] = OTHER_RAC_VALUES["DO_NOT_CLIMB"]

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
