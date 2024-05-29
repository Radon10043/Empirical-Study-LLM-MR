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
    def test34(self, job_list: list):  # Fixed
        """Metamorphic Relation 34: The order of process PIDs after several BLOCK operations should reverse upon several UNBLOCK
        operations with a ratio that places them back in the opposite order."""
        # Assuming 'job_list' are such that all jobs start unblocked and 'ratio' is such that UNBLOCK reverses order
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        ratio = "0.0"  # Add processes back in reverse order; dependent on the scheduler's implementation
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        source_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).rstrip().split(" ")
        source_out.remove("")  # Remove empty string from split

        # Block all jobs
        follow_op = str()
        for _ in range(job_cnt):
            follow_op += SCHEDULE_OPERATIONS["BLOCK"] + "\n"

        # Unblock all jobs in reverse order
        for _ in range(job_cnt):
            follow_op += f"{SCHEDULE_OPERATIONS['UNBLOCK']} {ratio}\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Get the order of processes after several UNBLOCK operations
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).rstrip().split(" ")
        follow_out.remove("")  # Remove empty string from split

        # Verification: The order of processes should be reversed after unblocking compared to the intended initial order
        self.assertEqual(source_out[::-1], follow_out)


if __name__ == "__main__":
    unittest.main()
