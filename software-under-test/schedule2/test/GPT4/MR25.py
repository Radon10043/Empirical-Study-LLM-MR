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
    def test25(self, job_list: list):  # Fixed
        """Metamorphic Relation 25: Alternating between BLOCK and UNBLOCK for a process without any other operations in between
        should result in the original order of the process before any BLOCK operations."""
        # Perform a block followed by unblock on the current process
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        source_op = SCHEDULE_OPERATIONS["BLOCK"] + "\n" + SCHEDULE_OPERATIONS["UNBLOCK"] + " 1.0\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Capture the order after block and unblock
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split()

        # Perform FLUSH to get the original order of processes
        follow_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Verification: The order after block and unblock should be the same as the original order
        self.assertEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
