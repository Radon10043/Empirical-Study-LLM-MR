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
    def test41(self, vals: list):
        """Metamorphic Relation 41: If the Other_RAC is set to DO_NOT_CLIMB and the TCAS system of the other aircraft is not active, then changing the value of Two_of_Three_Reports_Valid should lead to the same output as changing the value of Alt_Layer_Value."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_CLIMB"] and vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["NO_INTENT"]:
            # Construct follow-up input 1: Changing Two_of_Three_Reports_Valid
            follow_report_vals = vals.copy()
            follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1 - follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]]
            follow_report_out = run_tcas(follow_report_vals)

            # Construct follow-up input 2: Changing Alt_Layer_Value
            follow_layer_vals = vals.copy()
            follow_layer_vals[INDEX["Alt_Layer_Value"]] = 1 - follow_layer_vals[INDEX["Alt_Layer_Value"]]
            follow_layer_out = run_tcas(follow_layer_vals)

            # Verification
            self.assertEqual(follow_report_out, follow_layer_out)


if __name__ == "__main__":
    unittest.main()
