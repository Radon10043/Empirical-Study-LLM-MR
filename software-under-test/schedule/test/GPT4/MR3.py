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
    def test3(self, job_list: list):
        """Metamorphic Relation 3: A job's expiration of time quantum should place it back based on its priority."""
        # Execute quantum expiration for the current top priority job
        source_op = [SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the source operations
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split()

        # Finish the current top priority job and then execute quantum expiration for the next job
        follow_op = [SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Execute the follow-up operations
        follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split()

        # The first element from the source_out should be equivalent to the second element in follow_out
        # (since the first job was finished before expiring quantum in follow-up case)
        self.assertEqual(source_out[0], follow_out[1])

        # The remaining elements in the source output should then match the rest of the elements in follow_out
        source_out.pop(0)
        follow_out.pop(0)
        follow_out.pop(0)
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
