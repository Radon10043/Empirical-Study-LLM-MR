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
    def test16(self, job_list: list): # Fixed
        """Metamorphic Relation 16: Flushing a certain state and then restoring it back with NEW_JOB should result in the same 
        output as flushing after restoring the state."""
        # Get the initial state's output of process PIDs after a flush
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op_flush = SCHEDULE_OPERATIONS["FLUSH"]
        source_output = subprocess.check_output(cmd_list, input=source_op_flush, text=True).split("\n")

        # Restore back all processes that were flushed using NEW_JOB operations
        cmd_list_restore = [SCHEDULE_PATH]
        for pid in source_output:
            if pid:  # Ignore empty strings that might come from split
                restore_job_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + " " + pid + "\n"
                cmd_list_restore.append(restore_job_op)

        # Flush to capture the follow-up output
        follow_output = subprocess.check_output(cmd_list_restore, input=source_op_flush, text=True).split("\n")

        # Verification: The output sequence of PIDs after restoring and flushing should match initial state's output
        self.assertEqual(source_output, follow_output)


if __name__ == "__main__":
    unittest.main()
