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
    def test31(self, job_list: list):   # Fixed
        """The order of scheduling should remain consistent after all processes are terminated and a new set of processes is added."""
        INITIAL_PROCESS_COUNT = 100
        REPLENISH_PROCESS_COUNT = 100

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Sequence of operations to add and then flush processes
        initial_add_flush_ops = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}" for _ in range(INITIAL_PROCESS_COUNT)] + [SCHEDULE_OPERATIONS["FLUSH"]]

        # Capture the output for initial process addition and flushing
        initial_output = subprocess.check_output(cmd_list, input="\n".join(initial_add_flush_ops), text=True).strip()

        # Add new set of processes after previous ones have been flushed
        replenish_ops = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}" for _ in range(REPLENISH_PROCESS_COUNT)]

        # Capture the output after replenishment
        replenish_output = subprocess.check_output(cmd_list, input="\n".join(replenish_ops), text=True).strip()

        # Test whether scheduling behavior is consistent before and after process pool depletion and replenishment
        self.assertEqual(initial_output, replenish_output)


if __name__ == "__main__":
    unittest.main()
