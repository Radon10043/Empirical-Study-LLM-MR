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
    def test33(self, vals: list):
        """Metamorphic Relation 33: For a non-TCAS equipped other aircraft, the change in reported Other_RAC values from DO_NOT_CLIMB to DO_NOT_DESCEND or vice versa should not affect the advisory determination."""
        if vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["TCAS_TA"]:
            return  # Skip test if the other aircraft is TCAS equipped

        other_rac_values = (OTHER_RAC_VALUES["DO_NOT_CLIMB"], OTHER_RAC_VALUES["DO_NOT_DESCEND"])

        for other_rac in other_rac_values:
            vals[INDEX["Other_RAC"]] = other_rac

            # Get the advisory result with the first Other_RAC value
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in vals]
            cmd_list.extend(tmp_list)
            first_out = subprocess.check_output(cmd_list, text=True).strip()

            # Now change to the opposite Other_RAC value and get the new advisory result
            follow_vals = vals.copy()
            follow_vals[INDEX["Other_RAC"]] = other_rac_values[1] if other_rac == other_rac_values[0] else other_rac_values[0]

            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            second_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(first_out, second_out, "Changing Other_RAC from DO_NOT_CLIMB to DO_NOT_DESCEND or vice versa incorrectly altered the advisory.")


if __name__ == "__main__":
    unittest.main()
