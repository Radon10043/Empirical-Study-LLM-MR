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
    def test18(self, job_list: list):  # Fixed
        """Metamorphic Relation 18: Upgrading the priority of a job and then finishing it should result in the same system state as
        finishing the job first without an upgrade, assuming there are no other jobs at the upgraded priority."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Upgrade the priority of the first job and then finish it
        source_op = SCHEDULE_OPERATIONS["UPGRADE_PRIO"] + " " + PRIORITY_LEVEL["MEDIUM"] + " 1\n" + SCHEDULE_OPERATIONS["FINISH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Get the state after the above operations
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Now finish the job first without upgrade
        follow_op = SCHEDULE_OPERATIONS["FINISH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        follow_op = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The state of the system should be the same in both cases
        self.assertEqual(source_out, follow_op)


if __name__ == "__main__":
    unittest.main()
