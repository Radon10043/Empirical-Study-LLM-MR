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
    def test21(self, job_list: list):   # Fixed
        """Metamorphic Relation 21: Upgrading a process priority and then downgrading it back to the original should not change the order of processes."""
        # Add a job and upgrade its priority, then downgrade it back and flush
        upgrade_downgrade_ops = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}",
            f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1",
            f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['MEDIUM']} 0.0001",
            SCHEDULE_OPERATIONS['FLUSH']
        ]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        upgrade_downgrade_out = subprocess.check_output(cmd_list, input="\n".join(upgrade_downgrade_ops), text=True).strip()

        # Add a job and then immediately flush, without altering its priority
        add_flush_ops = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}",
            SCHEDULE_OPERATIONS['FLUSH']
        ]

        add_flush_out = subprocess.check_output(cmd_list, input="\n".join(add_flush_ops), text=True).strip()

        # Verify that upgrade followed by immediate downgrade does not affect the order
        self.assertEqual(upgrade_downgrade_out, add_flush_out)


if __name__ == "__main__":
    unittest.main()
