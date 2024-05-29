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
    def test4(self, job_list: list):    # Fixed
        """Metamorphic Relation 4: Blocking and immediately unblocking a process should lead to an identical system
        state as before these operations were applied, assuming no other operations are invoked in between."""
        ratio = 1

        # Get source state snapshot by copying the list of jobs
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Perform blocking operation on the current process
        block_op = SCHEDULE_OPERATIONS["BLOCK"] + "\n"
        source_out = subprocess.check_output(cmd_list, input=block_op, text=True).split("\n")

        # Unblock the same process with a ratio implying it would return to the same priority level
        unblock_op = SCHEDULE_OPERATIONS["UNBLOCK"] + " " + str(ratio) + "\n"
        follow_out = subprocess.check_output(cmd_list, input=unblock_op, text=True)

        # Verification: The job list state should be the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
