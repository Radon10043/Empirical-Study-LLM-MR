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
    def test15(self, vals: list):
        """Metamorphic Relation 15: If Two_of_Three_Reports_Valid is set to 1, and Own_Tracked_Alt is equal to Other_Tracked_Alt, changing the value of Other_RAC should not change the output."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1
        follow_vals[INDEX["Other_RAC"]] = (follow_vals[INDEX["Other_RAC"]] + 1) % len(OTHER_RAC_VALUES)  # Change Other_RAC

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        if vals[INDEX["Own_Tracked_Alt"]] == vals[INDEX["Other_Tracked_Alt"]]:
            self.assertEqual(source_out, follow_out)
        else:
            self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
