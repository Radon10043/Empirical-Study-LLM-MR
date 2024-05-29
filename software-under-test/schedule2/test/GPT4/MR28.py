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
    def test28(self, job_list: list): # Fixed
        """Metamorphic Relation 28: Issuing a FLUSH command multiple times should result in the same empty state each time."""
        # Initial FLUSH operation
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # First check after the first FLUSH
        source_op = SCHEDULE_OPERATIONS["FLUSH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")
        source_out.pop(0)

        # Second check after the second FLUSH (should be no change)
        follow_op = source_op + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")
        follow_out.pop(0)

        # Verification: The state after the second flush should be the same as after the first flush (both empty)
        self.assertEqual("".join(source_out), "".join(follow_out))


if __name__ == "__main__":
    unittest.main()
