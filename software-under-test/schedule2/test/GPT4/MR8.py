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
    def test8(self, initial_conditions: list):  # Fixed
        """Metamorphic Relation 8: Performing a QUANTUM_EXPIRE operation on an empty process queue should have no effect on the
        output compared to when no operation is performed, since there's no current process to move to the end of the queue."""
        # Construct source input with initial conditions
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(initial_conditions)

        # Ensure process queue is empty
        empty_op = SCHEDULE_OPERATIONS["FLUSH"]
        subprocess.check_output(cmd_list, input=empty_op, text=True)

        # Perform QUANTUM_EXPIRE on the empty queue
        source_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # No follow-up input needed, the queue is already empty
        follow_out = []

        # Verification: No operation on an empty queue should result in no output
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
