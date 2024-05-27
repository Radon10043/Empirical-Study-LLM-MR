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
    def test34(self, vals: list):
        """Metamorphic Relation 34: If the other aircraft's intention changes, and the Own_Above_Threat and Own_Below_Threat parameters are preserved, the output should change according to the new intention."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Other_RAC"]] == 2:  # Assuming a downward intention
            follow_vals[INDEX["Other_RAC"]] = 1  # Changing the intention to an upward advisory
        elif vals[INDEX["Other_RAC"]] == 1:  # Assuming an upward intention
            follow_vals[INDEX["Other_RAC"]] = 2  # Changing the intention to a downward advisory

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
