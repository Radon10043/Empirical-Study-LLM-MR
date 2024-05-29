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
    def test30(self, job_list: list):  # Fixed
        """Metamorphic Relation 30: For a given priority level, adding and then immediately finishing a set of jobs should
        leave the system state identical to its state had the jobs not been added."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        source_out = subprocess.check_output(cmd_list, input=SCHEDULE_OPERATIONS["FLUSH"], text=True).split()

        # Add and then immediately finish jobs
        follow_op = str()
        for _ in range(5):  # Assume 5 jobs are created and finished
            follow_op += f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}\n"
            follow_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Flush the system to get the final state output
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The system state after adding and finishing jobs should be the same as the original state
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
