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
    def test24(self, vals: list):
        """Metamorphic Relation 24: If the Other_Capability is set to TCAS_TA, the report validity is 1, and the Intruder aircraft has the intent to climb, then the output should not change when the value of Climb_Inhibit is changed."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["TCAS_TA"] and vals[INDEX["Two_of_Three_Reports_Valid"]] == 1 and vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_DESCEND"]:
            follow_vals[INDEX["Climb_Inhibit"]] = (follow_vals[INDEX["Climb_Inhibit"]] + 1) % 2  # Change Climb_Inhibit

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
