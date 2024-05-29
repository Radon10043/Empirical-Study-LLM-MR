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
    def test38(self, job_list: list):  # Fixed
        """Metamorphic Relation 38: Executing a FLUSH operation right after starting the scheduler should result in an empty output,
        regardless of the initial scheduling queue state."""
        # Initial FLUSH operation
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True)

        # Perform an additional FLUSH
        output = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"] + SCHEDULE_OPERATIONS["FLUSH"], text=True).split("\n")
        output.pop(0)

        # Verification: Output after additional FLUSH should be empty (no jobs should be present)
        self.assertEqual("".join(output), "")


if __name__ == "__main__":
    unittest.main()
