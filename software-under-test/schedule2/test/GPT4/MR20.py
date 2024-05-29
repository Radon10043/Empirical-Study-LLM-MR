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
    def test20(self, job_list: list):   # Fixed
        """Metamorphic Relation 20: Upgrading a job's priority, blocking, unblocking, and then downgrading the priority back to the original 
        should result in the same job order upon flush as it was initially."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Add a job and then change its priority
        source_op = f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}\n"
        source_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1.0\n"

        # Block and then unblock the job
        source_op += SCHEDULE_OPERATIONS["BLOCK"] + "\n"
        source_op += f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1.0\n"

        # Downgrade the priority back to the original
        source_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['HIGH']} 0.0\n"

        # Capture the output after flushing
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Prepare the follow-up command list to compare with original
        follow_op = f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Capture the follow-up output after flushing
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The output should be the same, as the job returns to its original priority
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
