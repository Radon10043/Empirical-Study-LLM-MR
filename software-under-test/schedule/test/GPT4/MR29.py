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
    def test29(self, job_list: list):   # Fixed
        """The system should be robust against duplicate commands and produce consistent outcomes regardless of repeated commands."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Schedule a new job then repeat the same command
        schedule_ops_with_duplicates = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}"]  # Assuming the scheduler is robust against such duplicates.

        # Flush the queue
        flush_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        # Capture the output after including duplicate commands
        ops_sequence = schedule_ops_with_duplicates + flush_op
        output_with_duplicates = subprocess.check_output(cmd_list, input="\n".join(ops_sequence), text=True).strip()

        # Compare with output without duplicates
        ops_sequence_no_duplicates = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}"] + flush_op
        output_no_duplicates = subprocess.check_output(cmd_list, input="\n".join(ops_sequence_no_duplicates), text=True).strip()

        # Verifying that the system's behavior is consistent regardless of duplicates
        self.assertEqual(output_with_duplicates, output_no_duplicates)


if __name__ == "__main__":
    unittest.main()
