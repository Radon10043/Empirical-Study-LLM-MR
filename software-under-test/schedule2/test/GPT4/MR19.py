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
    def test19(self, job_list: dict):   # Fixed
        """Metamorphic Relation 19: Flushing after adding a series of jobs should give the same output if repeated with the same operations."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Add jobs with varying priorities and capture the expected flush output
        source_op = str()
        for priority in [PRIORITY_LEVEL["LOW"], PRIORITY_LEVEL["MEDIUM"], PRIORITY_LEVEL["HIGH"]]:
            for _ in range(3):  # Add three jobs per priority
                source_op += f"{SCHEDULE_OPERATIONS['NEW_JOB']} {priority}\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Flush the scheduler and save the output
        first_flush_output = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Repeat the same operations and flush again
        second_flush_output = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Verification: The output from both flush operations should be the same
        self.assertEqual(first_flush_output, second_flush_output)


if __name__ == "__main__":
    unittest.main()
