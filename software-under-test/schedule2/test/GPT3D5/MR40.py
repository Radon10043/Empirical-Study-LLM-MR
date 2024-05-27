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

    # Fixed
    @parameterized.expand(load_test_cases(1000))
    def test_metamorphic_relation_40(self, job_list: list):
        """Metamorphic Relation 40: The result of flushing the scheduler state followed by finishing a process will be the same as finishing the process first and then flushing the scheduler state."""
        # Get source output
        source_op = SCHEDULE_OPERATIONS["FLUSH"] + "\n" + SCHEDULE_OPERATIONS["FINISH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).replace("\n", "")

        # Construct follow-up input
        follow_op = SCHEDULE_OPERATIONS["FINISH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).replace("\n", "")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
