import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
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
    def test28(self, vals: list):
        """Metamorphic Relation 28: If reliable reports are below the threshold ('High_Confidence' or 'Two_of_Three_Reports_Valid' is false), changing the 'Alt_Layer_Value' should not affect the resolution advisory."""
        # Check if reliable reports are below threshold
        if vals[INDEX["High_Confidence"]] or vals[INDEX["Two_of_Three_Reports_Valid"]]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        alt_layer_values = [0, 1, 2, 3]  # Assuming 4 different altitude layer values

        for alt_layer_value in alt_layer_values:
            if alt_layer_value == vals[INDEX["Alt_Layer_Value"]]:
                continue  # Skip the current value

            # Construct follow-up input changing 'Alt_Layer_Value'
            follow_vals = vals.copy()
            follow_vals[INDEX["Alt_Layer_Value"]] = alt_layer_value

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(source_out, follow_out, f"Changing 'Alt_Layer_Value' to {alt_layer_value} affected the resolution advisory in a scenario where reports are unreliable.")


if __name__ == "__main__":
    unittest.main()
