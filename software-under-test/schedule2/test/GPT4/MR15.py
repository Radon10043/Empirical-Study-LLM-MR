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
    def test15(self, job_list: list): # Fixed
        """Metamorphic Relation 15: Adding a process to a non-empty queue and immediately flushing should result in the same 
        output as flushing before adding the process, with the addition of the newly added process's PID at the end."""
        # Get the PID output from flushing before adding a new process
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        output_before = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Add a new process and then flush
        follow_op = SCHEDULE_OPERATIONS["FLUSH"] + "\n" + SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["LOW"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        output_after = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The output after should have one additional PID at the end
        self.assertEqual("".join(output_before), "".join(output_after))


if __name__ == "__main__":
    unittest.main()
