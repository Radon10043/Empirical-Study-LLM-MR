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
    def test1(self, job_list: list):
        """Metamorphic Relation 1: If the size of a job-list is 1, then the operation that moving the job at the top of this list to the end will not affect the output."""
        if job_list[0] != "1":
            return

        # Get source output
        source_op = SCHEDULE_OPERATIONS["FLUSH"]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Construct follow-up input
        follow_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
