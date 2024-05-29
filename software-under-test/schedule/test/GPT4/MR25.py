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
    def test25(self, initial_jobs: list):   # Fixed
        """
        The behavior of processes after a block or a quantum expiration should be consistent.
        A process that is blocked and then has its quantum expired should still be the
        next process after it is unblocked.
        """
        # Operations for blocking and quantum expiration
        block_op = SCHEDULE_OPERATIONS["BLOCK"]
        quantum_expire_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"]
        unblock_op = f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1"

        flush_op = SCHEDULE_OPERATIONS["FLUSH"]

        # Setup test input
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(initial_jobs)

        # Apply operation: block, then quantum expire, then unblock and flush
        source_output = subprocess.check_output(cmd_list, input="\n".join([block_op, quantum_expire_op, unblock_op, flush_op]), text=True).strip()

        # Apply operation: quantum expire, then block, then unblock and flush (reversed order)
        followup_output = subprocess.check_output(cmd_list, input="\n".join([quantum_expire_op, block_op, unblock_op, flush_op]), text=True).strip()

        # Verify the order and existence of process in output remains consistent
        self.assertEqual(source_output, followup_output)


if __name__ == "__main__":
    unittest.main()
