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
    def test12(self, job_list: list): # Fixed
        """Metamorphic Relation 12: Blocking the current job (BLOCK), followed by UNBLOCK with a specific ratio that ensures it returns
        to its original priority and then adding additional jobs, should not affect the order in which jobs are finished when a FLUSH is performed."""
        num_blocks = 3  # Number of times to block and unblock the current job
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        if job_cnt < 3:
            self.skipTest("Not enough jobs to perform the test")

        # Get the flushed state after initial blocking and unblocking
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op = str()
        for _ in range(num_blocks):
            source_op += SCHEDULE_OPERATIONS["BLOCK"] + "\n" + SCHEDULE_OPERATIONS["UNBLOCK"] + " 1.0\n"

        # Add additional jobs
        for _ in range(3):  # Assume we add 3 jobs for simplicity
            source_op += SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n"

        # Flush the scheduler and get the first flushed output
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Get the flushed output without blocking or unblocking but with same additional jobs added
        follow_op = str()
        for _ in range(3):  # Same number of additional jobs as in the source state
            follow_op += SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: Order of jobs finished after FLUSH should be the same for source and follow-up operations
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
