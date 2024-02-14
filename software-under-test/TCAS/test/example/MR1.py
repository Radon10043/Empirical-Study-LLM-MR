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
    def test1(self, vals: list):
        """Metamorphic Relation 1: If the relation of the Own_Tracked_Alt and Other_Tracked_Alt is not changed, meanwhile other parameter values are not changed too, then the outputs of the TCAS should be the same."""
        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Own_Tracked_Alt"]] *= 2
        follow_vals[INDEX["Other_Tracked_Alt"]] *= 2

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
