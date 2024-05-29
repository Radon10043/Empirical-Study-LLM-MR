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
    def test23(self, job_list: list):  # Fixed
        """Metamorphic Relation 23: The process order after an arbitrary number of QUANTUM_EXPIRE operations should not change
        provided no new jobs are added and no process is finished or blocked/unblocked."""
        # Perform an initial flush to get the current order of processes
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Perform QUANTUM_EXPIRE operations multiple times
        follow_op = str()
        for _ in range(10):  # Assume quantum expires 10 times
            follow_op += SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Flush to get the order after quantum expires
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The order of processes after quantum expires should be identical to the initial order
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
