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
    def test10(self, job_list: list):
        """Metamorphic Relation 10: Upgrading a process to its current priority level should not change the process termination order."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Upgrade job to same priority and finish all
        upgrade_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['HIGH']} 1", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the operations
        upgrade_out = subprocess.check_output(cmd_list, input="\n".join(upgrade_op), text=True).split()

        # Just add and then immediately flush processes
        normal_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the regular operations
        normal_out = subprocess.check_output(cmd_list, input="\n".join(normal_op), text=True).split()

        # The output should not change because the priority level remained the same
        self.assertEqual(upgrade_out, normal_out)


if __name__ == "__main__":
    unittest.main()
