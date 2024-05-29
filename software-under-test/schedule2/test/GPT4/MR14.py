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
    def test14(self, job_list: list):  # Fixed
        """Metamorphic Relation 14: Issuing a BLOCK operation to move the current process to the blocked queue followed by
        an UNBLOCK operation that restores it to the original priority should result in the process occupying the same
        position in the ready queue as it would occupy after a QUANTUM_EXPIRE operation."""
        # Perform BLOCK followed by UNBLOCK
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        source_op = SCHEDULE_OPERATIONS["BLOCK"] + "\n"
        # Assuming the priority before blocking was MEDIUM and the ratio restores it to the same position
        source_op += SCHEDULE_OPERATIONS["UNBLOCK"] + " 1.0\n"

        # Flush to capture the output after BLOCK and UNBLOCK operations
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Perform QUANTUM_EXPIRE to compare
        follow_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"

        # Flush to capture the output after QUANTUM_EXPIRE operation
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The order of processes after BLOCK+UNBLOCK should be same as QUANTUM_EXPIRE
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
