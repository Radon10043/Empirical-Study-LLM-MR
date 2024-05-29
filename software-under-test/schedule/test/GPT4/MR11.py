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
    def test11(self, job_list: list):
        """Metamorphic Relation 11: Two consecutive priority upgrades of a process should have the same effect as a single upgrade by two levels."""
        # Add a low priority job then upgrade it twice consecutively to a high priority
        upgrade_twice_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1", f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['MEDIUM']} 1", SCHEDULE_OPERATIONS["FLUSH"]]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        upgrade_twice_out = subprocess.check_output(cmd_list, input="\n".join(upgrade_twice_op), text=True).strip()

        # Add a low priority job then upgrade it directly to a high priority
        direct_upgrade_op = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1.9999", SCHEDULE_OPERATIONS["FLUSH"]]

        direct_upgrade_out = subprocess.check_output(cmd_list, input="\n".join(direct_upgrade_op), text=True).strip()

        # Verify that the result of upgrading twice and upgrading by two levels directly is the same
        self.assertEqual(upgrade_twice_out, direct_upgrade_out)


if __name__ == "__main__":
    unittest.main()
