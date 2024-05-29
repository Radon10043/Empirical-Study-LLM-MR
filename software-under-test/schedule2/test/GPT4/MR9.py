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
    def test9(self, initial_conditions: list):  # Fixed
        """Metamorphic Relation 9: Adding a series of jobs and then flushing should result in the output listing the 
        jobs in reverse order of their addition due to stack-like behavior of the operations."""
        num_jobs = 5

        # Construct initial input with initial conditions and perform a series of NEW_JOB operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(initial_conditions)
        for i in range(num_jobs):
            new_job_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n"
            cmd_list.append(new_job_op)

        # Perform FLUSH and capture source output
        source_op = "".join(cmd_list) + SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output([SCHEDULE_PATH], input=source_op, text=True).split("\n")

        # Perform same series of NEW_JOB operations but with FINISH after each to capture output PIDs in reverse
        follow_cmd_list = [SCHEDULE_PATH]
        follow_cmd_list.extend(initial_conditions)
        for i in range(num_jobs):
            new_job_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n"
            finish_op = SCHEDULE_OPERATIONS["FINISH"] + "\n"
            follow_cmd_list.append(new_job_op)
            follow_cmd_list.append(finish_op)

        # Capture the follow-up output
        follow_op = "".join(follow_cmd_list)
        follow_out = subprocess.check_output([SCHEDULE_PATH], input=follow_op, text=True).split("\n")[:-num_jobs]

        # Verification: Since the FINISH command removes the current job from the queue, the order of PIDs output should be reversed
        self.assertEqual(source_out, follow_out[::-1])


if __name__ == "__main__":
    unittest.main()
