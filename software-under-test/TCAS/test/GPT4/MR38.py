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
    def test38(self, vals: list):
        """Metamorphic Relation 38: If the initial advisory is to climb (UPWARD_RA), increasing the upward separation should not change the advisory."""
        # Obtain base output for comparison:
        base_cmd = [TCAS_PATH] + [str(x) for x in vals]
        base_out = subprocess.check_output(base_cmd, text=True).strip()
        if base_out != "1":  # If the initial advice is not UPWARD_RA, skip this case.
            return

        # Increase the upward separation:
        vals[INDEX["Up_Separation"]] += 1000  # Arbitrary increase in upward separation
        follow_up_cmd = [TCAS_PATH] + [str(x) for x in vals]
        follow_up_out = subprocess.check_output(follow_up_cmd, text=True).strip()

        # Check that the advisory hasn't changed:
        self.assertEqual(base_out, follow_up_out, "Increasing upward separation changed the UPWARD_RA advisory incorrectly.")


if __name__ == "__main__":
    unittest.main()
