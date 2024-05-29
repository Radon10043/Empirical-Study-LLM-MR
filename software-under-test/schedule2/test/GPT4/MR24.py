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
    def test24(self, job_list: list):
        """Metamorphic Relation 24: Completing (FINISH) the current job should not affect the output of subsequently executed
        BLOCK and UNBLOCK commands, given that there is no current job to block and unblock."""
        # Complete the current job
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op = SCHEDULE_OPERATIONS["FINISH"] + "\n"

        # Block and unblock commands with no current process
        source_op += SCHEDULE_OPERATIONS["BLOCK"] + "\n"
        source_op += SCHEDULE_OPERATIONS["UNBLOCK"] + " 1.0\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Perform FLUSH to get the order of processes
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split()

        # The output of processes should be the same as the state after the FINISH command
        follow_op = SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The list of processes should be the same after FINISH and BLOCK/UNBLOCK commands
        self.assertEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
