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
    def test13(self, job_list: list):  # Fixed
        """Metamorphic Relation 13: Executing the QUANTUM_EXPIRE operation multiple times in a row without intervening
        operations on a non-empty queue should not change the relative order of processes within their priority levels."""
        # Set up initial conditions and perform QUANTUM_EXPIRE multiple times
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        source_op = str()
        for _ in range(5):  # Arbitrarily chosen to expire five quantums
            source_op += SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"

        # Perform FLUSH to get the order of processes after quantum expirations
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Perform the same initial conditions and only one QUANTUM_EXPIRE to compare the ordering
        cmd_list_single_expire = [SCHEDULE_PATH]
        cmd_list_single_expire.extend(job_list)

        follow_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list_single_expire, input=follow_op, text=True).split("\n")

        # Verification: The relative order of processes with same priority should be the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
