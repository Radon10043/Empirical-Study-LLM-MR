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
    def test31(self, vals: list):
        """Metamorphic Relation 31: If High_Confidence is initially false and becomes true without Other_RAC indicating a climb or descent, it should not change the advisory from UNRESOLVED."""
        if vals[INDEX["High_Confidence"]] or vals[INDEX["Other_RAC"]] in (OTHER_RAC_VALUES["DO_NOT_CLIMB"], OTHER_RAC_VALUES["DO_NOT_DESCEND"]):
            return

        # Get source output with High_Confidence initially set to false
        vals[INDEX["High_Confidence"]] = 0
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # If the output is not UNRESOLVED, this test cannot be applied
        if source_out != "0":  # UNRESOLVED
            return

        # Change High_Confidence to true
        follow_vals = vals.copy()
        follow_vals[INDEX["High_Confidence"]] = 1

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        self.assertEqual(source_out, follow_out, "Changing High_Confidence from false to true altered the UNRESOLVED advisory.")


if __name__ == "__main__":
    unittest.main()
