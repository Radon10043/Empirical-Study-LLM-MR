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
    def test33(self, job_list: list):
        """
        Metamorphic Relation 24: Termination of independent processes should be consistent irrespective of the order in which they were terminated.
        """
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Add multiple processes and terminate them in a specific order
        operations_add_finish = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}",
            SCHEDULE_OPERATIONS["FINISH"],
            SCHEDULE_OPERATIONS["FINISH"],
            SCHEDULE_OPERATIONS["FINISH"],
            SCHEDULE_OPERATIONS["FLUSH"],
        ]

        output_order_1 = subprocess.check_output(cmd_list, input="\n".join(operations_add_finish), text=True).split()

        # Add the same processes and terminate them in reverse order
        operations_add_finish_reverse = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}",
            SCHEDULE_OPERATIONS["FINISH"],
            SCHEDULE_OPERATIONS["FINISH"],
            SCHEDULE_OPERATIONS["FINISH"],
            SCHEDULE_OPERATIONS["FLUSH"],
        ]

        output_order_2 = subprocess.check_output(cmd_list, input="\n".join(operations_add_finish_reverse), text=True).split()

        # Order of job terminations should remain consistent given independent jobs
        self.assertEqual(output_order_1, output_order_2)


if __name__ == "__main__":
    unittest.main()
