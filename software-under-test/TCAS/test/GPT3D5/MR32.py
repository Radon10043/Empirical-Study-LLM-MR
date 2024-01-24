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
    def test32(self, vals: list):
        """Metamorphic Relation 32: If the value of Up_Separation is less than the value of Down_Separation, and the TCAS system of the other aircraft is active, then switching the values of Alt_Layer_Value and Two_of_Three_Reports_Valid should lead to the same output."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Up_Separation"]] < vals[INDEX["Down_Separation"]] and vals[INDEX["Other_Capability"]] == 1:
            # Construct follow-up input: Switch Alt_Layer_Value and Two_of_Three_Reports_Valid
            follow_vals = vals.copy()
            follow_vals[INDEX["Alt_Layer_Value"]], follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = follow_vals[INDEX["Two_of_Three_Reports_Valid"]], follow_vals[INDEX["Alt_Layer_Value"]]
            follow_out = run_tcas(follow_vals)

            # Verification
            self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
