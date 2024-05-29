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
    def test32(self, job_list: list): # Fixed
        """Metamorphic Relation 31: Repeatedly upgrading and then downgrading the priority of all queued processes should
        result in the same order upon flush as upgrading and downgrading only once for each process."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Upgrade and then downgrade priority of all jobs repeatedly
        source_op = str()
        for _ in range(3):  # Repeat the upgrade and downgrade process 3 times for example
            for _ in job_list:  # Assuming job_list has as many entries as jobs
                source_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1.0\n"
                source_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['HIGH']} 0.0\n"
        source_op += SCHEDULE_OPERATIONS['FLUSH']

        # Capture the order after repeated priority changes
        repeated_changes_output = subprocess.check_output(cmd_list, input=source_op, text=True).split()

        # Now upgrade and downgrade priority only once for each job
        follow_op = str()
        for _ in job_list:
            follow_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1.0\n"
            follow_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['HIGH']} 0.0\n"
        follow_op += SCHEDULE_OPERATIONS['FLUSH']

        # Capture the order after a single round of priority changes
        single_change_output = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The order of FLUSH after repeated priority changes should match that of a single change
        self.assertEqual(repeated_changes_output, single_change_output)


if __name__ == "__main__":
    unittest.main()
