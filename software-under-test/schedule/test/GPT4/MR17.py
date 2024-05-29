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
    def test17(self, job_list: list):
        """Metamorphic Relation 17: Continuously blocking and unblocking the same process should have no impact on process order."""
        # Block and unblock the same process multiple times, then flush
        repeated_block_unblock_op = [
            SCHEDULE_OPERATIONS["BLOCK"],
            SCHEDULE_OPERATIONS["UNBLOCK"],
            SCHEDULE_OPERATIONS["BLOCK"],
            SCHEDULE_OPERATIONS["UNBLOCK"],
            SCHEDULE_OPERATIONS["FLUSH"]
        ]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        repeated_block_unblock_out = subprocess.check_output(cmd_list, input="\n".join(repeated_block_unblock_op), text=True).strip()

        # Flush all processes without blocking/unblocking
        simple_flush_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        simple_flush_out = subprocess.check_output(cmd_list, input="\n".join(simple_flush_op), text=True).strip()

        # Verify that the sequence of output IDs is the same
        self.assertEqual(repeated_block_unblock_out, simple_flush_out)


if __name__ == "__main__":
    unittest.main()
