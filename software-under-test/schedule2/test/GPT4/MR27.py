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
    def test27(self, job_list: list):
        """Metamorphic Relation 27: Blocking and unblocking a process with a particular ratio that places it back to its
        original queue position should not affect the execution order after a FLUSH,
        compared to not blocking/unblocking at all."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Capture initial FLUSH order
        source_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Perform block, then unblock with a ratio putting it back to the original position
        follow_op = SCHEDULE_OPERATIONS["BLOCK"] + "\n" + SCHEDULE_OPERATIONS["UNBLOCK"] + " 1.0\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Execute block and unblock sequence and capture new order
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: New order should be similar to the initial flush order
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
