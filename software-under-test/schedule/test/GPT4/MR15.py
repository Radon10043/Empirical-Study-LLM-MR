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
    def test15(self, job_list: list):
        """Metamorphic Relation 15: Adding a process and then immediately finishing should not affect the state."""
        # Add and finish the process multiple times
        add_finish_multiple_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", SCHEDULE_OPERATIONS["FINISH"], f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FLUSH"]]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        add_finish_multiple_out = subprocess.check_output(cmd_list, input="\n".join(add_finish_multiple_op), text=True).split()

        # Flush all processes after they are added
        flush_after_add_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", SCHEDULE_OPERATIONS["FLUSH"]]

        flush_after_add_out = subprocess.check_output(cmd_list, input="\n".join(flush_after_add_op), text=True).split()

        # The order of terminations should match because finishing jobs puts the system in the same state as if they were never added
        self.assertEqual(add_finish_multiple_out[:-1], flush_after_add_out[:-1])


if __name__ == "__main__":
    unittest.main()
