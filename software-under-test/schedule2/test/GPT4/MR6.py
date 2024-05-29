import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule2.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test6(self, initial_conditions: list):  # Fixed
        """Metamorphic Relation 6: Adding a job with LOW priority followed by upgrading its priority to HIGH should result
        in the same output as directly adding a job with HIGH priority when a FLUSH operation is applied."""
        # Construct source input with initial conditions and perform NEW_JOB with LOW, then UPGRADE_PRIO to HIGH, and FLUSH
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(initial_conditions)
        source_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n" + SCHEDULE_OPERATIONS["UPGRADE_PRIO"] + " " + PRIORITY_LEVEL["LOW"] + " 1.0\n" + SCHEDULE_OPERATIONS["UPGRADE_PRIO"] + " " + PRIORITY_LEVEL["MEDIUM"] + " 1.0\n" + SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Construct follow-up input with initial conditions and perform direct NEW_JOB with HIGH priority, then FLUSH
        follow_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["HIGH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The outputs should be the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
