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
    def test39(self, vals: list):
        """Metamorphic Relation 39: If the intruder issues a DO_NOT_CLIMB and the own aircraft receives a DOWNWARD_RA, the same advisory should be received even if the intruder subsequently issues a DO_NOT_DESCEND if all other parameters are constant."""
        # Set the Other_RAC to DO_NOT_CLIMB and get the current output:
        vals[INDEX["Other_RAC"]] = OTHER_RAC_VALUES["DO_NOT_CLIMB"]
        base_cmd = [TCAS_PATH] + [str(x) for x in vals]
        base_out = subprocess.check_output(base_cmd, text=True).strip()

        if base_out != "2":  # If the advice is not DOWNWARD_RA, skip this case.
            return

        # Now set the Other_RAC to DO_NOT_DESCEND and get the output:
        vals[INDEX["Other_RAC"]] = OTHER_RAC_VALUES["DO_NOT_DESCEND"]
        follow_up_cmd = [TCAS_PATH] + [str(x) for x in vals]
        follow_up_out = subprocess.check_output(follow_up_cmd, text=True).strip()

        # Check the output is unchanged
        self.assertEqual(base_out, follow_up_out, "Changing Other_RAC from DO_NOT_CLIMB to DO_NOT_DESCEND incorrectly altered the DOWNWARD_RA advisory when it should not have.")


if __name__ == "__main__":
    unittest.main()
