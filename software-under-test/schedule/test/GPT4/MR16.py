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
    def test16(self, job_list: list):
        """Metamorphic Relation 16: Operations that are not related to the state of a process should not affect the termination order or output."""
        # Perform unrelated operations (block/unblock) between adding processes
        add_with_unrelated_ops = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            SCHEDULE_OPERATIONS["BLOCK"],
            SCHEDULE_OPERATIONS["UNBLOCK"],
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            SCHEDULE_OPERATIONS["FLUSH"],
        ]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        add_with_unrelated_out = subprocess.check_output(cmd_list, input="\n".join(add_with_unrelated_ops), text=True)

        # Add processes without unrelated operations
        add_without_unrelated_ops = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FLUSH"]]

        add_without_unrelated_out = subprocess.check_output(cmd_list, input="\n".join(add_without_unrelated_ops), text=True)

        # Output sequence should be unaffected by block/unblock commands when there were no jobs blocked
        self.assertEqual(add_with_unrelated_out, add_without_unrelated_out)


if __name__ == "__main__":
    unittest.main()
