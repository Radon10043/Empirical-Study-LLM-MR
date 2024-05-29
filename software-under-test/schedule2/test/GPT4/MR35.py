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
    def test35(self, job_list: list):
        """Metamorphic Relation 35: Blocking and then unblocking the same process, assuming no time-sensitive priority changes,
        should not alter the sequence of process IDs in the output after a FLUSH, compared to not blocking/unblocking."""
        # Capture initial FLUSH order
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Perform block then unblock command sequence
        follow_op = SCHEDULE_OPERATIONS["BLOCK"] + "\n"
        follow_op += f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1.0\n"  # Ratio 1.0 to return to original position
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Execute block/unblock sequence and capture new order
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: New order after block/unblock should be identical to the initial flush order
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
