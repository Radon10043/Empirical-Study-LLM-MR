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
    def test33(self, vals: list):
        """Metamorphic Relation 33: If the Other_Tracked_Alt is greater than Own_Tracked_Alt, then changing the reported intruder's RAC value should not change the output."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Other_Tracked_Alt"]] > vals[INDEX["Own_Tracked_Alt"]]:
            # Construct follow-up input: Change Other_RAC
            follow_vals = vals.copy()
            follow_vals[INDEX["Other_RAC"]] = 1 if follow_vals[INDEX["Other_RAC"]] == 0 else 0
            follow_out = run_tcas(follow_vals)

            # Verification
            self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
