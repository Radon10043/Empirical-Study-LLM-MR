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
    def test9(self, job_list: list):
        """Metamorphic Relation 9: The blocked queue should behave like a FIFO (first-in, first-out) queue."""
        # Block three processes and then unblock them in the same order they were blocked
        block_unblock_op = [SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1", f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1", f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        block_unblock_out = subprocess.check_output(cmd_list, input="\n".join(block_unblock_op), text=True).split()

        # Reverse the order of unblocking
        reverse_unblock_op = [SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], f"{SCHEDULE_OPERATIONS['UNBLOCK']} 0.9999", f"{SCHEDULE_OPERATIONS['UNBLOCK']} 0.9999", f"{SCHEDULE_OPERATIONS['UNBLOCK']} 0.9999", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the reverse unblocking operations
        reverse_unblock_out = subprocess.check_output(cmd_list, input="\n".join(reverse_unblock_op), text=True).split()

        # Verify that the order of process termination remains the same because unblocking should be FIFO
        self.assertEqual(block_unblock_out, reverse_unblock_out)


if __name__ == "__main__":
    unittest.main()
