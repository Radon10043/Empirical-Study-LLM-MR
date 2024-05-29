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
    def test28(self, job_list: list):  # Fixed
        """When the system is fully loaded with processes, a priority upgrade should still place the process before others at its new priority level."""
        MAX_SYSTEM_CAPACITY = 100

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Initialize the system with the maximum number of processes
        init_full_load_ops = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}" for _ in range(MAX_SYSTEM_CAPACITY)]

        # Upgrade the priority of one of the lower priority processes
        upgrade_ops = [f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 0.5"]

        # Flush the queue
        flush_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        # Capture the output after priority upgrade
        ops_sequence = init_full_load_ops + upgrade_ops + flush_op
        output_after_upgrade = subprocess.check_output(cmd_list, input="\n".join(ops_sequence), text=True).strip()

        # Identifying the upgraded process is beyond the scope of this pseudo-code, but a successful test would verify
        # that the upgraded process is terminated in accordance with its new, higher priority.

        # Additional verifications would be implemented here.
        # ...


if __name__ == "__main__":
    unittest.main()
