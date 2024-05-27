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
    def test8(self, vals: list):
        """Metamorphic Relation 8: Swapping the 'Up_Separation' and 'Down_Separation' values should not affect the advisory if 'Own_Tracked_Alt' remains unchanged."""
        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Up_Separation"]], follow_vals[INDEX["Down_Separation"]] = follow_vals[INDEX["Down_Separation"]], follow_vals[INDEX["Up_Separation"]]

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
