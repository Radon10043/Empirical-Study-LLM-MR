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
    def test39(self, job_list: list):  # Fixed
        """Metamorphic Relation 39: Successive executions of the BLOCK operation for all jobs and a subsequent single FLUSH
        operation should give the same result as one FLUSH operation performed without any BLOCKs."""
        # Perform the BLOCK operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        source_op = str()
        for _ in range(job_cnt):  # Block all jobs in the initial condition
            source_op += SCHEDULE_OPERATIONS["BLOCK"] + "\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Perform the FLUSH operation
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split()

        # Compare with the output of FLUSH without BLOCKs
        follow_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Verification: Outputs of both approaches should give the same result
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
