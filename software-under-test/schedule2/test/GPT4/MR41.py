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
    def test41(self, job_list: list): # Fixed
        """Metamorphic Relation 41: The order of finishing jobs should be the same regardless of the number of QUANTUM_EXPIRE operations
        performed when all jobs have constant priority levels."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        # Directly finish all jobs to capture the finish order
        source_op = str()
        for _ in range(job_cnt):
            source_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).strip()

        # Perform QUANTUM_EXPIRE operations before each FINISH operation to capture the finish order
        follow_op = str()
        for _ in range(job_cnt):
            follow_op += SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"
            follow_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).strip()

        # Verification: The order of finished jobs should be the same regardless of QUANTUM_EXPIRE operations
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
