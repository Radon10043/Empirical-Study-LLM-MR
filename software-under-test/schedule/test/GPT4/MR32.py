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
    def test32(self, job_list: list):
        """After a reset operation, the system should return to a valid and consistent initial state, and subsequent operations should behave as if starting fresh."""
        # Initially populate the system with processes
        populate_system_ops = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}",
            # ... any other setup operations
        ]

        # Perform some operations that modify system state
        modify_state_ops = [
            SCHEDULE_OPERATIONS["BLOCK"],
            f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 1",
            # ... other operations that affect the state
        ]

        # Reset the system (assuming there is a RESET command that could be sent)
        reset_system_op = [SCHEDULE_OPERATIONS["RESET"]]

        # Capture system output after reset to ensure it is in its initial state
        # ... execution and output capture

        # Verify the system is in its initial valid state
        # ... verification code

        # Perform operations again as if starting fresh and verify output matches expectations
        # ... execution and output verification after reset


if __name__ == "__main__":
    unittest.main()
