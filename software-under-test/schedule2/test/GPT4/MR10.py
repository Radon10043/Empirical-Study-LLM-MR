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
    def test10(self, process_queue: list):  # Fixed
        """Metamorphic Relation 10: Repeatedly expiring quantum for the current job without adding new jobs or performing other
        operations should result in the same job sequence being output on FLUSH, since the current job moves to the end of its queue."""
        # Capture the initial sequence after a flush
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(process_queue)
        flush_op = SCHEDULE_OPERATIONS["FLUSH"]
        initial_sequence = subprocess.check_output(cmd_list, input=flush_op, text=True).split("\n")

        # Simulate quantum expire multiple times
        job_cnt = int(process_queue[0])
        quantum_expire_op = str()
        for _ in range(job_cnt):
            quantum_expire_op += SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"
        final_sequence = subprocess.check_output(cmd_list, input=quantum_expire_op + SCHEDULE_OPERATIONS["FLUSH"], text=True).split("\n")

        # Verification: The sequence of PIDs from the initial and final flush should remain the same
        self.assertEqual(initial_sequence, final_sequence)


if __name__ == "__main__":
    unittest.main()
