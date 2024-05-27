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

    # Fixed
    @parameterized.expand(load_test_cases(1000))
    def test_metamorphic_relation_32(self, job_list: list):
        """Metamorphic Relation 32: Adding a new job with a specific priority followed by upgrading the priority for the same process will have the same result as first adding the new job and then flushing the scheduler state."""
        # Get source output
        source_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n" + SCHEDULE_OPERATIONS["UPGRADE_PRIO"] + " " + PRIORITY_LEVEL["LOW"] + " " + "0.9999" + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Construct follow-up input
        follow_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
