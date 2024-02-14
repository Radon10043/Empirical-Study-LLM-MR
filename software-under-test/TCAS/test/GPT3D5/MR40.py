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
    def test40(self, vals: list):
        """Metamorphic Relation 40: If the Intruder's altitude changes to be the same as the own aircraft's altitude and the Own_Above_Threat state changes, the TCAS output should change accordingly."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Other_Tracked_Alt"]] = vals[INDEX["Own_Tracked_Alt"]]  # Making the intruder's altitude the same as own aircraft's altitude
        follow_vals[INDEX["Own_Above_Threat"]] = not follow_vals[INDEX["Own_Above_Threat"]]  # Changing the Own_Above_Threat state

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
