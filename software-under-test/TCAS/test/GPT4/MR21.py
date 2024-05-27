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
    def test21(self, vals: list):
        """Metamorphic Relation 21: Permuting the order of the altitude layers should not change the resolution advisory as long as other parameters suggest a specific maneuver is needed."""
        original_alt_layer_value = vals[INDEX["Alt_Layer_Value"]]
        other_alt_layer_values = [(original_alt_layer_value + i) % 4 for i in range(1, 4)]  # Assuming 4 altitude layers

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        for layer_value in other_alt_layer_values:
            # Construct follow-up input
            follow_vals = vals.copy()
            follow_vals[INDEX["Alt_Layer_Value"]] = layer_value

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(source_out, follow_out, f"Changing the altitude layer from {original_alt_layer_value} to {layer_value} incorrectly altered the advisory.")


if __name__ == "__main__":
    unittest.main()
