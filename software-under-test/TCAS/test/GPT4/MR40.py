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
    def test40(self, vals: list):
        """Metamorphic Relation 40: If the initial output is UNRESOLVED with a non-TCAS-equipped intruder, adding TCAS capability to the intruder without changing its intent should not resolve the advisory."""
        # Ensure the other aircraft is not TCAS-equipped:
        vals[INDEX["Other_Capability"]] = OTHER_CAPABILITY_VALUES["OTHER"]
        base_cmd = [TCAS_PATH] + [str(x) for x in vals]
        base_out = subprocess.check_output(base_cmd, text=True).strip()
        if base_out != "0":  # If the initial output is not UNRESOLVED, skip this case.
            return

        # Now add TCAS capability to the intruder aircraft:
        vals[INDEX["Other_Capability"]] = OTHER_CAPABILITY_VALUES["TCAS_TA"]
        follow_up_cmd = [TCAS_PATH] + [str(x) for x in vals]
        follow_up_out = subprocess.check_output(follow_up_cmd, text=True).strip()

        # Check the output is still UNRESOLVED
        self.assertEqual(base_out, follow_up_out, "Adding TCAS capability to an intruder with no intent incorrectly changed the UNRESOLVED advisory.")


if __name__ == "__main__":
    unittest.main()
