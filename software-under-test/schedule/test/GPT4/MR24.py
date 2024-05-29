import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test24(self, initial_jobs: list):   # Fixed
        """
        Processes with higher priority are always scheduled before those with lower priority.
        Adding a lower-priority job should not affect the order of existing higher-priority jobs.
        """
        # Operations for adding multiple processes of different priorities
        add_low_priority_op = f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}"
        add_high_priority_op = f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}"

        # Flush output to observe termination order
        flush_op = SCHEDULE_OPERATIONS["FLUSH"]

        # Setup test input
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(initial_jobs)

        # Apply operation: add high followed by low priority, then flush
        source_output = subprocess.check_output(cmd_list, input="\n".join([add_high_priority_op, add_low_priority_op, flush_op]), text=True).strip()

        # Apply operation: add low followed by high priority, then flush
        followup_output = subprocess.check_output(cmd_list, input="\n".join([add_low_priority_op, add_high_priority_op, flush_op]), text=True).strip()

        # Order of high priority termination should be consistent despite order they were added
        self.assertEqual(source_output, followup_output)


if __name__ == "__main__":
    unittest.main()
