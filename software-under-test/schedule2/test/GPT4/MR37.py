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
    def test37(self, job_list: list):    # Fixed
        """Metamorphic Relation 37: Issuing a FINISH command sequentially until all processes are finished should produce
        the same output as a single FLUSH command that terminates all processes at once."""
        # FLUSH all processes at once
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])

        source_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()  # Flush to clear out any initial state

        follow_op = str()
        for _ in job_list:
            follow_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The output after finishing all processes one by one should match the output from flushing
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
