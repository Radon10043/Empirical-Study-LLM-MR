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
    def test33(self, job_list: list):  # Fixed
        """Metamorphic Relation 33: Executing QUANTUM_EXPIRE should not change the output list after FLUSH, as it should only
        move the current job to the end of its priority queue, without affecting the final flush order."""
        # Perform initial FLUSH to get the order of jobs
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Execute QUANTUM_EXPIRE and then perform FLUSH
        follow_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The final order after QUANTUM_EXPIRE should match the initial flush order
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
