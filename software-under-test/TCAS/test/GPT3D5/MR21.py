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
    def test21(self, vals: list):
        """Metamorphic Relation 21: If the inputs from the intruder aircraft (Other_Tracked_Alt, Other_Tracked_Alt_Rate) are halved, the advisories output from the TCAS should remain the same."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Other_Tracked_Alt"]] = follow_vals[INDEX["Other_Tracked_Alt"]] / 2
        follow_vals[INDEX["Other_Tracked_Alt_Rate"]] = follow_vals[INDEX["Other_Tracked_Alt"]] / 2

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
