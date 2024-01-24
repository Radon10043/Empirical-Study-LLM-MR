from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test19(self, vals: list):
        """Metamorphic Relation 19: Given that the Vertical separation is greater than 300, if the Thresh_Vertical_Sep is changed from 0 to 1, the output should not change."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Cur_Vertical_Sep"]] > 300:
            follow_vals[INDEX["Thresh_Vertical_Sep"]] = 1

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
