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
    def test21(self, job_list: dict):
        """Metamorphic Relation 21: Finish all processes in a non-empty queue and compare the output
        with the queue without these processes. Addition and immediate termination of a process should
        not affect the order of remaining processes."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Finish all processes and save the output order
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])
        source_op = str()
        for _ in range(job_cnt):  # Assuming the number of initial conditions matches the number of jobs added
            source_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Flush without finishing and save the output order
        follow_op = SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The output of finished processes should equal the flushed state without any jobs
        self.assertEqual("".join(source_out), "".join(follow_out))


if __name__ == "__main__":
    unittest.main()
