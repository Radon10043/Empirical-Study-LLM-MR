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
    def test7(self, job_list: list):
        """Metamorphic Relation 7: Finishing a process before or after upgrading other processes should not change the order of remaining processes."""
        # Upgrade a medium priority job and then finish the highest priority job
        source_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1", SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the source operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split()

        # Finish the highest priority job and then upgrade a medium priority job
        follow_op = [SCHEDULE_OPERATIONS["FINISH"], f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the follow-up operations
        follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split()

        # Verify that the sequence of remaining processes is the same
        self.assertListEqual(source_out[1:], follow_out[1:])  # excluding the first process which is finished first in the follow_up


if __name__ == "__main__":
    unittest.main()
