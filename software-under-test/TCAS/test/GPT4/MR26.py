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
    def test26(self, vals: list):
        """Metamorphic Relation 26: Altering the 'Other_Capability' from TCAS equipped to non-equipped should not alter the advisory when 'Other_RAC' signifies no intention (NO_INTENT)."""
        if vals[INDEX["Other_RAC"]] != OTHER_RAC_VALUES["NO_INTENT"]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Construct follow-up input: Switch 'Other_Capability' between TCAS-equipped and not.
        follow_vals = vals.copy()
        follow_vals[INDEX["Other_Capability"]] = OTHER_CAPABILITY_VALUES["OTHER"] if vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["TCAS_TA"] else OTHER_CAPABILITY_VALUES["TCAS_TA"]

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        self.assertEqual(source_out, follow_out, "Changing the 'Other_Capability' altered the output where it should not.")


if __name__ == "__main__":
    unittest.main()
