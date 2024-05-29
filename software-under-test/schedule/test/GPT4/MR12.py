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
    def test12(self, job_list: list):
        """Metamorphic Relation 12: Multiple quantum expirations without intervening actions should not change the process order."""
        # Expire the quantum of the top process twice
        quantum_twice_op = [SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        quantum_twice_out = subprocess.check_output(cmd_list, input="\n".join(quantum_twice_op), text=True).split()

        # Expire the quantum of the top process once
        quantum_once_op = [SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

        quantum_once_out = subprocess.check_output(cmd_list, input="\n".join(quantum_once_op), text=True).split()

        # Since consecutive quantum expirations without interference do not introduce new processes or change priorities, the process order should remain the same.
        self.assertEqual(quantum_twice_out, quantum_once_out)


if __name__ == "__main__":
    unittest.main()
