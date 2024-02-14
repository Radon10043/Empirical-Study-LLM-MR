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
    def test22(self, vals: list):
        """Metamorphic Relation 22: If the intruder aircraft has an intention to descend, and the altitude thresholds for positive resolution advisories are incremented, the TCAS output should recommend a downward resolution advisory."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        if vals[INDEX["Other_RAC"]] == 2:  # Assuming a downward intention
            follow_vals[INDEX["ALIM()"]] = vals[INDEX["ALIM()"]] + 100  # Incrementing the altitude thresholds for positive resolution advisories

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertEqual(follow_out, 2)  # Expecting a recommendation for a downward resolution advisory


if __name__ == "__main__":
    unittest.main()
