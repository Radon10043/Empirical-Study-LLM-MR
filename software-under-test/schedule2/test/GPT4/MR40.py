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
    def test40(self, job_list: list):   # Fixed
        """Metamorphic Relation 40: After adding a set of jobs, alternating between QUANTUM_EXPIRE and FINISH should finish all jobs without
        affecting the order in which jobs are selected to run, thus should maintain ordering based on priority."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        # Alternate between QUANTUM_EXPIRE and FINISH to run through jobs in priority order
        source_op = str()
        for _ in range(job_cnt):
            source_op += SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"
            source_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Perform flush to get the order
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split()

        # Add jobs again and flush directly to determine expected order
        follow_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Verification: The order after alternating QUANTUM_EXPIRE and FINISH should match the order from a direct flush
        self.assertEqual(source_op, follow_out)


if __name__ == "__main__":
    unittest.main()
