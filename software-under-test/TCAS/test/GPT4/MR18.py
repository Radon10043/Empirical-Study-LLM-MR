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
    def test18(self, vals: list):
        """Metamorphic Relation 18: If Own_Tracked_Alt and Other_Tracked_Alt are both increased or decreased by an equal altitude step without changing their relative positions, the resolution advisory should not change."""
        altitude_steps = [1000, -1000]  # Example steps for own and other aircraft altitude changes

        for step in altitude_steps:
            # Get source output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in vals]
            cmd_list.extend(tmp_list)
            source_out = subprocess.check_output(cmd_list, text=True).strip()

            # Construct follow-up input
            follow_vals = vals.copy()
            follow_vals[INDEX["Own_Tracked_Alt"]] += step
            follow_vals[INDEX["Other_Tracked_Alt"]] += step

            # Make sure the altitude does not exceed any system limits
            if follow_vals[INDEX["Own_Tracked_Alt"]] < 0 or follow_vals[INDEX["Other_Tracked_Alt"]] < 0:
                continue

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(source_out, follow_out, "Advisory should remain unchanged when both aircraft altitudes change by the same amount.")


if __name__ == "__main__":
    unittest.main()
