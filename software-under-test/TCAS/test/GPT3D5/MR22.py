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
    def test22(self, vals: list):
        """Metamorphic Relation 22: If the Other_RAC is set to DO_NOT_DESCEND, and the TCAS system of the other aircraft is not active, changing the value of Other_Capability should not change the output."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_DESCEND"] and vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["NO_INTENT"]:
            follow_vals[INDEX["Other_Capability"]] = (follow_vals[INDEX["Other_Capability"]] + 1) % 2  # Change Other_Capability

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
