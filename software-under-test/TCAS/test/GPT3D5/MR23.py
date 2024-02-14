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
    def test23(self, vals: list):
        """Metamorphic Relation 23: If the intruder aircraft's capability changes from being TCAS equipped to not being TCAS equipped, but the own aircraft's altitude and other parameters remain the same, the output should remain the same."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if follow_vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["TCAS_TA"]:
            follow_vals[INDEX["Other_Capability"]] = OTHER_CAPABILITY_VALUES["OTHER"]
        elif follow_vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["OTHER"]:
            follow_vals[INDEX["Other_Capability"]] = OTHER_CAPABILITY_VALUES["TCAS_TA"]

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
