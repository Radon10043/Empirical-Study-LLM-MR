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
    def test17(self, job_list: list): # Fixed
        """Metamorphic Relation 17: After adding multiple new jobs, the application of the FLUSH operation should output the PIDs of
        the jobs in the same order in which they were added."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Add jobs with ascending PIDs and store their expected order
        expected_order = []
        for i in range(5):  # Add five new jobs, for example
            pid = str(i + 100)  # Assign a PID for illustration
            expected_order.append(pid)
            cmd_list.append(SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n")

        # Apply FLUSH operation
        flush_op = SCHEDULE_OPERATIONS["FLUSH"]
        actual_order = subprocess.check_output(cmd_list, input=flush_op, text=True).split("\n")

        # Verification: The actual order of PIDs should match the expected order
        self.assertEqual(expected_order, actual_order)


if __name__ == "__main__":
    unittest.main()
