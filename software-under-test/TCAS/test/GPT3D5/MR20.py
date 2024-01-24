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
    def test20(self, vals: list):
        """Metamorphic Relation 20: If the own aircraft has a climb intention and the other aircraft has a do not climb intention, changing the state of Other_Capability should not change the output."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Climb_Inhibit"]] == 0 and vals[INDEX["Other_RAC"]] == OTHER_RAC_VALUES["DO_NOT_CLIMB"]:
            follow_vals[INDEX["Other_Capability"]] = (follow_vals[INDEX["Other_Capability"]] + 1) % 2  # Change Other_Capability

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
