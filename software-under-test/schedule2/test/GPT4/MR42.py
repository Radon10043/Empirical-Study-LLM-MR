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
    def test42(self, job_list: list): # Fixed
        """Metamorphic Relation 42: When all jobs are moved to a blocked state, flushing the system should produce no output."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        # Block all jobs
        source_op = str()
        for _ in range(job_cnt):
            source_op += SCHEDULE_OPERATIONS["BLOCK"] + "\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Flush and capture any output
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).strip()

        # Verification: Flushing a system with only blocked jobs should produce no output
        self.assertEqual(source_out, "")


if __name__ == "__main__":
    unittest.main()
