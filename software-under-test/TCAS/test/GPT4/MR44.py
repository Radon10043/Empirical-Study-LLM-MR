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
    def test44(self, vals: list):   # Fixed
        """Metamorphic Relation 44: If the intruder aircraft makes a large climb or descent, the own aircraft should be advised the opposite direction, provided it's originally at a significant vertical separation."""
        large_movement = 2000  # Value for significant climb/descent by the intruder
        significant_sep = 5000  # Value for significant vertical separation

        vals[INDEX["Cur_Vertical_Sep"]] += significant_sep

        # Initial vertical separation is significant
        if vals[INDEX["Cur_Vertical_Sep"]] < significant_sep:
            return

        # Set intruder altitude movement
        intruder_movement = large_movement if vals[INDEX["Own_Tracked_Alt"]] > vals[INDEX["Other_Tracked_Alt"]] else -large_movement
        vals[INDEX["Other_Tracked_Alt"]] += intruder_movement

        # Get source output
        cmd_list = [TCAS_PATH] + [str(x) for x in vals]
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Establish the expected advisory direction based on intruder's movement
        expected_out = "1" if intruder_movement > 0 else "2"  # 1 = UPWARD_RA, 2 = DOWNWARD_RA

        # Verification
        self.assertEqual(source_out, expected_out, "Advisory did not reflect opposite action of intruder's large movement.")


if __name__ == "__main__":
    unittest.main()
