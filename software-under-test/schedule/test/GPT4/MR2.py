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
    def test2(self, job_list: list):
        """Metamorphic Relation 2: Blocking and then immediately unblocking a process should not affect the
        sequence of process termination."""
        # Execute block followed by unblock
        source_op = [SCHEDULE_OPERATIONS["BLOCK"], f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the source operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split()

        # Flush the processes without blocking/unblocking
        follow_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the follow-up operations
        follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split()

        # Verify that the outputs are the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
