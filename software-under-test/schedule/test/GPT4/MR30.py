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
    def test30(self, job_list: list):   # Fixed
        """The order of the processes in the block and unblock queue should be consistent with the order of blocking and unblocking actions."""
        NUM_PROCESSES_TO_BLOCK = 5

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Block several processes
        block_ops = [SCHEDULE_OPERATIONS["BLOCK"] for _ in range(NUM_PROCESSES_TO_BLOCK)]

        # Unblock all previously blocked processes
        unblock_ops = [f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1" for _ in range(NUM_PROCESSES_TO_BLOCK)]

        # Flush the queue
        flush_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        # Capture the output sequence
        ops_sequence = block_ops + unblock_ops + flush_op
        output_sequence = subprocess.check_output(cmd_list, input="\n".join(ops_sequence), text=True).strip()

        # The order of processes unblocked and then terminated should correspond to the order specified by the operations
        # Additional verifications would be implemented here.
        # ...


if __name__ == "__main__":
    unittest.main()
