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
    def test20(self, job_list: list):
        """Metamorphic Relation 20: Adding and then removing processes before any other operations should lead back to the initial state."""
        # Add and remove a process sequence, then flush
        add_remove_sequence = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FINISH"], f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute an empty flush operation for comparison (since previous operations should not alter the final state)
        flush_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        add_remove_out = subprocess.check_output(cmd_list, input="\n".join(add_remove_sequence), text=True).strip()
        flush_out = subprocess.check_output(cmd_list, input="\n".join(flush_op), text=True).strip()

        # Ensure that the state after add-remove sequence is equivalent to the flushed state
        self.assertEqual(add_remove_out, flush_out)


if __name__ == "__main__":
    unittest.main()
