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
    def test23(self, job_list: list):
        """Metamorphic Relation 23: Multiple block and unblock operations on processes should produce a consistent process termination order."""
        # Add some processes, block and unblock them, then flush
        block_unblock_repeat_ops = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            SCHEDULE_OPERATIONS["BLOCK"],
            SCHEDULE_OPERATIONS["UNBLOCK"],
            SCHEDULE_OPERATIONS["BLOCK"],
            SCHEDULE_OPERATIONS["UNBLOCK"],
            SCHEDULE_OPERATIONS["FLUSH"],
        ]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        block_unblock_repeat_out = subprocess.check_output(cmd_list, input="\n".join(block_unblock_repeat_ops), text=True).split()

        # Add some processes and flush them without block/unblock
        simple_add_flush_ops = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["FLUSH"]]

        simple_add_flush_out = subprocess.check_output(cmd_list, input="\n".join(simple_add_flush_ops), text=True).split()

        # Verify that block/unblock operations do not affect process termination order
        self.assertEqual(block_unblock_repeat_out, simple_add_flush_out)


if __name__ == "__main__":
    unittest.main()
