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
    def test11(self, job_list: list): # Fixed
        """Metamorphic Relation 11: When a process is added (NEW_JOB) and subsequently finished (FINISH) before any other operations,
        the system state should remain unchanged as if no process was ever added."""
        # Get system state before adding a new job
        cmd_list_before = [SCHEDULE_PATH]
        cmd_list_before.extend(job_list)
        source_op_before = SCHEDULE_OPERATIONS["FLUSH"]
        source_state_before = subprocess.check_output(cmd_list_before, input=source_op_before, text=True).split("\n")

        # Add new job and finish it immediately
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        new_and_finish_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n" + SCHEDULE_OPERATIONS["FINISH"] + SCHEDULE_OPERATIONS["FLUSH"]
        source_state_after = subprocess.check_output(cmd_list, input=new_and_finish_op, text=True).split("\n")

        # Verification: Both before and after states should be identical
        self.assertEqual(source_state_before, source_state_after)


if __name__ == "__main__":
    unittest.main()
