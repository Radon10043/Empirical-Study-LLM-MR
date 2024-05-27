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
    def test42(self, vals: list):
        """Metamorphic Relation 42: Increasing the reliability of altitude reports (i.e., setting High_Confidence to true) should not result in a less conservative resolution advisory."""
        # Scenario: Two of three reports are initially valid and confidence is low
        vals[INDEX["High_Confidence"]] = 0
        vals[INDEX["Two_of_Three_Reports_Valid"]] = 1

        # Get baseline output advisory
        base_cmd = [TCAS_PATH] + [str(x) for x in vals]
        base_out = subprocess.check_output(base_cmd, text=True).strip()

        # Increase reliability by setting High_Confidence to true
        vals[INDEX["High_Confidence"]] = 1

        # Get output after increasing report reliability
        follow_up_cmd = [TCAS_PATH] + [str(x) for x in vals]
        follow_up_out = subprocess.check_output(follow_up_cmd, text=True).strip()

        # Verify output is not less conservative (i.e., does not switch from UPWARD_RA/DOWNWARD_RA to UNRESOLVED)
        if base_out in ["1", "2"] and follow_up_out == "0":
            self.fail("Increasing report reliability led to a less conservative advisory.")


if __name__ == "__main__":
    unittest.main()
