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
    def test36(self, vals: list):
        """Metamorphic Relation 36: If the Other_RAC is set to DO_NOT_CLIMB, and the value of Alt_Layer_Value is 1 or 2, then changing the value of Other_Capability should lead to the same output as changing the value of Two_of_Three_Reports_Valid."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Other_RAC"]] == 1 and vals[INDEX["Alt_Layer_Value"]] in [1, 2]:
            # Construct follow-up input 1: Changing Other_Capability
            follow_capability_vals = vals.copy()
            follow_capability_vals[INDEX["Other_Capability"]] = 1 - follow_capability_vals[INDEX["Other_Capability"]]
            follow_capability_out = run_tcas(follow_capability_vals)

            # Construct follow-up input 2: Changing Two_of_Three_Reports_Valid
            follow_report_vals = vals.copy()
            follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1 - follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]]
            follow_report_out = run_tcas(follow_report_vals)

            # Verification
            self.assertEqual(follow_capability_out, follow_report_out)


if __name__ == "__main__":
    unittest.main()
