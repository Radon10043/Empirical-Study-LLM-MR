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
        """Metamorphic Relation 18: If the main logic for deciding the resolution advisory is not influenced, changing the altitude limits for providing a resolution advisory should not affect the output."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["ALIM()"]] += 100  # Changing the altitude limits for providing a resolution advisory

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
