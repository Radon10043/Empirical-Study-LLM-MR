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
    def test18(self, job_list: list):
        """Metamorphic Relation 18: The order of processes should remain the same after multiple quantum expirations."""
        # Cause quantum expiration twice before flushing
        quantum_order_op = [
            SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"],
            SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"],
            SCHEDULE_OPERATIONS["FLUSH"]
        ]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        quantum_order_out = subprocess.check_output(cmd_list, input="\n".join(quantum_order_op), text=True).split()

        # Only flush processes without quantum expiration
        no_quantum_flush_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        no_quantum_flush_out = subprocess.check_output(cmd_list, input="\n".join(no_quantum_flush_op), text=True).split()

        # Quantum expiration should not have changed the order the processes are flushed (terminated)
        self.assertEqual(quantum_order_out, no_quantum_flush_out)


if __name__ == "__main__":
    unittest.main()
