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
    def test36(self, job_list: list): # Fixed
        """Metamorphic Relation 36: Processes finished after a series of QUANTUM_EXPIRE operations should produce the same set 
        of PIDs in the output as processes finished without QUANTUM_EXPIRE, assuming no other jobs enter the system."""
        # Finished processes without QUANTUM_EXPIRE
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        source_op = str()
        for _ in range(job_cnt):  # Assuming job_list contains one entry per process
            source_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split()

        # Finished processes after QUANTUM_EXPIRE
        follow_op = str()
        for _ in range(job_cnt):
            follow_op += SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"
            follow_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The PIDs in the output should be identical regardless of QUANTUM_EXPIRE
        self.assertEqual(set(source_out), set(follow_out))


if __name__ == "__main__":
    unittest.main()
