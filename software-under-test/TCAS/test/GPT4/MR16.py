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
    def test16(self, vals: list):
        """Metamorphic Relation 16: If the own aircraft is at its maximum altitude, climbing should not be an advisory regardless of Other_RAC."""
        max_altitude = 60000  # Example max altitude for the testcase
        if vals[INDEX["Own_Tracked_Alt"]] < max_altitude:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        if source_out == "1":  # UPWARD_RA should not be advised at max altitude
            self.fail(f"At max altitude, UPWARD_RA should not be an advisory, got {source_out}")


if __name__ == "__main__":
    unittest.main()
