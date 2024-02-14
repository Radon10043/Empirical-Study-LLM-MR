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
    def test3(self, vals: list):
        """Metamorphic Relation 3: Given that the intruder aircraft does not have the TCAS system, if we change the state that the report describing the presence of any intruder is valid or not, the output should not change."""
        if vals[INDEX["Other_Capability"]] != OTHER_CAPABILITY_VALUES["OTHER"]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        if follow_vals[INDEX["Two_of_Three_Reports_Valid"]] != 0:
            follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = 0
        else:
            follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
