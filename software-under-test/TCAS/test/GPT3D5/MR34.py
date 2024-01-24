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
    def test34(self, vals: list):
        """Metamorphic Relation 34: If the high confidence is set to 1, and the Up_Separation is less than 300, changing the value of Other_RAC should lead to the same output as changing the value of Two_of_Three_Reports_Valid."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["High_Confidence"]] == 1 and vals[INDEX["Up_Separation"]] < 300:
            # Construct follow-up input 1: Changing Other_RAC
            follow_rac_vals = vals.copy()
            follow_rac_vals[INDEX["Other_RAC"]] = (follow_rac_vals[INDEX["Other_RAC"]] + 1) % len(OTHER_RAC_VALUES)
            follow_rac_out = run_tcas(follow_rac_vals)

            # Construct follow-up input 2: Changing Two_of_Three_Reports_Valid
            follow_two_of_three_vals = vals.copy()
            follow_two_of_three_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1 - follow_two_of_three_vals[INDEX["Two_of_Three_Reports_Valid"]]
            follow_two_of_three_out = run_tcas(follow_two_of_three_vals)

            # Verification
            self.assertEqual(follow_rac_out, follow_two_of_three_out)


if __name__ == "__main__":
    unittest.main()
