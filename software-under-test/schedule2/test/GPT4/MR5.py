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
    def test5(self, job_list: list):
        """Metamorphic Relation 5: For a given set of jobs, finishing the current job and then running quantum expire
        should yield the same result as running quantum expire and then finishing the job, since in both cases
        the current job is removed and the next job becomes the current."""
        # Get source output by performing FINISH followed by QUANTUM_EXPIRE
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op = SCHEDULE_OPERATIONS["FINISH"] + "\n" + SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Construct follow-up input by performing QUANTUM_EXPIRE followed by FINISH
        follow_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n" + SCHEDULE_OPERATIONS["FINISH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
