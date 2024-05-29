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
    def test26(self, job_list: list):  # Fixed
        """Metamorphic Relation 26: The order of process PIDs in the output after a sequence of 'block' operations
        followed by a corresponding sequence of 'unblock' operations should be identical to the initial order when flushed."""
        # Initial conditions setup and block all processes
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])
        source_op = str()
        for _ in range(job_cnt):  # Assuming job_list contains one entry per process
            source_op += SCHEDULE_OPERATIONS["BLOCK"] + "\n"

        # Unblock all processes with the same order they were blocked
        for _ in range(job_cnt):
            source_op += SCHEDULE_OPERATIONS["UNBLOCK"] + " 0.0\n"

        # Flush and capture the order after block/unblock operations
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Setup for initial flush without block/unblock
        follow_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split("\n")

        # Verification: The order of PIDs after block/unblock should match the order of an initial flush
        self.assertEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
