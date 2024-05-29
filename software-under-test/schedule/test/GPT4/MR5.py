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
    def test5(self, job_list: list):
        """Metamorphic Relation 5: Priority upgrades should not change the order of existing higher priority jobs."""
        # Add high priority job and then upgrade a medium priority job
        source_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['MEDIUM']} 1", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the source operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split()

        # Only add high priority job to the follow-up list
        follow_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the follow-up operations
        follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split()

        # Verify that the ID of the high priority job is the same in both cases
        self.assertEqual(source_out[0], follow_out[0])


if __name__ == "__main__":
    unittest.main()
