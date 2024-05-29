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
    def test1(self, job_list: list):
        """Metamorphic Relation 1: The order of adding independent jobs should not affect the output."""
        # Add two jobs with different priorities
        source_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the source operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split()

        # Add the same jobs in reverse order
        follow_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the follow-up operations
        follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split()

        # Verify that the outputs are the same
        self.assertEqual(sorted(source_out), sorted(follow_out))


if __name__ == "__main__":
    unittest.main()
