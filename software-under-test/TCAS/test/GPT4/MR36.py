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
    def test36(self, vals: list):
        """Metamorphic Relation 36: For an intruder with no climb or descend intent, flipping the Climb_Inhibit flag should not alter a resolved advisory to an unresolved one."""
        if vals[INDEX["Other_RAC"]] not in [OTHER_RAC_VALUES["NO_INTENT"]]:
            return  # Relation holds only when the intruder has NO_INTENT

        # Collect outputs for both Climb_Inhibit states
        climb_inhibit_states = [0, 1]
        advisories = []

        for state in climb_inhibit_states:
            vals[INDEX["Climb_Inhibit"]] = state

            # Collect output for the current Climb_Inhibit state
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in vals]
            cmd_list.extend(tmp_list)
            out = subprocess.check_output(cmd_list, text=True).strip()
            advisories.append(out)

        # Verification
        resolvable_states = ["1", "2"]  # UPWARD_RA and DOWNWARD_RA
        if all(advisory in resolvable_states for advisory in advisories):
            self.assertEqual(advisories[0], advisories[1], "Flipping the Climb_Inhibit flag altered a resolved advisory.")


if __name__ == "__main__":
    unittest.main()
