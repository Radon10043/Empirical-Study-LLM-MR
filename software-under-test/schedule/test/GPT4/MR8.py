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
    def test8(self, job_list: list):
        """Metamorphic Relation 8: Finishing processes when there are no processes left should not produce any output."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Execute flush to finish all existing jobs
        flush_op = [SCHEDULE_OPERATIONS["FLUSH"]]
        subprocess.check_output(cmd_list, input="\n".join(flush_op), text=True)

        # Try finishing jobs on an empty list
        finish_op = [SCHEDULE_OPERATIONS["FINISH"]]
        finish_out = subprocess.check_output(cmd_list, input="\n".join(finish_op), text=True).strip()

        # Since no processes exist, there should be no output
        self.assertEqual(finish_out, "")


if __name__ == "__main__":
    unittest.main()
