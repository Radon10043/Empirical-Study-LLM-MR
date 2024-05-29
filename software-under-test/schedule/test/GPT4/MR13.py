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
    def test13(self, job_list: list):
        """Metamorphic Relation 13: After a higher priority process is added, the preempted process should be executed after the new high priority process finishes."""
        # Add a low priority job, then expire its quantum to make it the currently running process, and add a higher priority job
        add_preempt_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FLUSH"]]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        add_preempt_out = subprocess.check_output(cmd_list, input="\n".join(add_preempt_op), text=True).split()

        # Add a low priority job and a high priority job before letting the low priority job run
        add_normal_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FLUSH"]]

        add_normal_out = subprocess.check_output(cmd_list, input="\n".join(add_normal_op), text=True).split()

        # The process IDs of the high priority jobs should appear first in both outputs
        self.assertEqual(add_preempt_out[0], add_normal_out[0])
        # The low priority job ID should be present in the output and it should match in both cases, indicating it runs after the higher priority job
        self.assertEqual(add_preempt_out[1], add_normal_out[1])


if __name__ == "__main__":
    unittest.main()
