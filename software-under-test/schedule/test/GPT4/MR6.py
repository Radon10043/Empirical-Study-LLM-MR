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
    def test6(self, job_list: list):
        """Metamorphic Relation 6: The order of unblocking should not matter if all processes get unblocked before termination."""
        # Block two processes and then unblock them in the same order
        source_op = [SCHEDULE_OPERATIONS['BLOCK'],
                    SCHEDULE_OPERATIONS['BLOCK'],
                    f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1",
                    f"{SCHEDULE_OPERATIONS['UNBLOCK']} 1",
                    SCHEDULE_OPERATIONS['FLUSH']]

        # Execute the source operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split()

        # Block two processes and then unblock them in reverse order
        follow_op = [SCHEDULE_OPERATIONS['BLOCK'],
                    SCHEDULE_OPERATIONS['BLOCK'],
                    f"{SCHEDULE_OPERATIONS['UNBLOCK']} 0.9999",
                    f"{SCHEDULE_OPERATIONS['UNBLOCK']} 0.9999",
                    SCHEDULE_OPERATIONS['FLUSH']]

        # Execute the follow-up operations
        follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split()

        # Verify that the sequence of termination is the same in both cases
        self.assertListEqual(sorted(source_out), sorted(follow_out))


if __name__ == "__main__":
    unittest.main()
