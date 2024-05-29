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
    def test27(self, job_list: list):  # Fixed
        """
        Determine the scheduler's behavior when trying to add a process
        upon reaching theoretical maximum capacity (process overflow).
        This relies on knowing the maximum process capacity, which is assumed to be 'n'.
        """
        n = 100

        MAX_PROCESSES = n  # Define the maximum capacity if known.
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Sequence for adding the maximum number of processes
        ops_add_max_processes = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}" for _ in range(MAX_PROCESSES)]
        ops_add_max_processes.append(SCHEDULE_OPERATIONS["FLUSH"])

        # Sequence for adding beyond maximum capacity
        ops_add_overflow_process = ops_add_max_processes.copy()
        ops_add_overflow_process.insert(len(ops_add_max_processes) // 2, f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}")

        output_max_processes = subprocess.check_output(cmd_list, input="\n".join(ops_add_max_processes), text=True).strip()
        output_overflow_process = subprocess.check_output(cmd_list, input="\n".join(ops_add_overflow_process), text=True).strip()

        # Assuming overflow is handled gracefully, both outputs should be identical.
        self.assertEqual(output_max_processes, output_overflow_process)


if __name__ == "__main__":
    unittest.main()
