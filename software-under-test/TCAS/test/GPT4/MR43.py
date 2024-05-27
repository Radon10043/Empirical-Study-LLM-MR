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
    def test43(self, vals: list):
        """Metamorphic Relation 43: Swapping the Own_Tracked_Alt and Other_Tracked_Alt, without changing their rates, should result in the opposite advisory when a change is warranted."""
        # Obtain an advisory with the original altitudes
        base_cmd = [TCAS_PATH] + [str(x) for x in vals]
        base_out = subprocess.check_output(base_cmd, text=True).strip()

        # Swap the Own_Tracked_Alt and Other_Tracked_Alt
        own_alt = vals[INDEX["Own_Tracked_Alt"]]
        vals[INDEX["Own_Tracked_Alt"]] = vals[INDEX["Other_Tracked_Alt"]]
        vals[INDEX["Other_Tracked_Alt"]] = own_alt

        # Obtain a new advisory after the swap
        follow_up_cmd = [TCAS_PATH] + [str(x) for x in vals]
        follow_up_out = subprocess.check_output(follow_up_cmd, text=True).strip()

        # Determine if the advisories are opposite or unchanged
        opposite = {"1": "2", "2": "1"}
        expected_follow_up_out = opposite.get(base_out, base_out)

        # Verify the advisories are as expected
        if not (follow_up_out == expected_follow_up_out or follow_up_out == base_out):
            error_msg = f"After swapping altitudes, expected advisory to be {expected_follow_up_out}, " f"but got {follow_up_out} instead."
            self.fail(error_msg)


if __name__ == "__main__":
    unittest.main()
