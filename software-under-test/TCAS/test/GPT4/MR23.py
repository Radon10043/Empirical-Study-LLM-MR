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
    def test23(self, vals: list):
        """Metamorphic Relation 23: Changing the Alt_Layer_Value to mimic a different altitude layer should not affect the resolution advisory if the High_Confidence flag is false and at least two altitude reports are not valid."""
        if vals[INDEX["High_Confidence"]] or vals[INDEX["Two_of_Three_Reports_Valid"]]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Try all different values of Alt_Layer_Value under test conditions
        for i in range(0, 4):
            if i == vals[INDEX["Alt_Layer_Value"]]:
                continue  # Skip the original value

            # Construct follow-up input
            follow_vals = vals.copy()
            follow_vals[INDEX["Alt_Layer_Value"]] = i

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(source_out, follow_out, f"Altering Alt_Layer_Value to {i} under low confidence changed the advisory.")


if __name__ == "__main__":
    unittest.main()
