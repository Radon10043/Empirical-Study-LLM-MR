from utils import *


def swap_climb_decision(decision):
    if decision == 0:
        return 2
    elif decision == 2:
        return 0
    else:
        return 1


def invert_decision(decision):
    if decision == 0:
        return 2
    elif decision == 2:
        return 0
    else:
        return 1


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test8(self, vals: list):
        """Metamorphic Relation 8: If the climb decision is changed to a descend decision, the output should be the inverse (0 becomes 2, 2 becomes 0, 1 remains the same)."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Climb_Inhibit"]] = swap_climb_decision(follow_vals[INDEX["Climb_Inhibit"]])

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(invert_decision(source_out), follow_out)


if __name__ == "__main__":
    unittest.main()
