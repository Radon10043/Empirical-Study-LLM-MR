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
    def test19(self, job_list: list):
        """Metamorphic Relation 19: A mix of operations including block, unblock, and process completion should lead to predictable scheduler states."""
        # Add a job, block a job, unblock a job, and terminate a job, then flush
        mixed_ops_sequence_1 = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Perform a different sequence of operations that should result in the same final state
        mixed_ops_sequence_2 = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}", SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["FLUSH"]]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        out_sequence_1 = subprocess.check_output(cmd_list, input="\n".join(mixed_ops_sequence_1), text=True).split()
        out_sequence_2 = subprocess.check_output(cmd_list, input="\n".join(mixed_ops_sequence_2), text=True).split()

        # The output of both sequences should lead to the same state, thus same termination output
        self.assertEqual(out_sequence_1, out_sequence_2)


if __name__ == "__main__":
    unittest.main()
