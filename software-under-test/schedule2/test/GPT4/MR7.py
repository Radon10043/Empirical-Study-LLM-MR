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
    def test7(self, job_list: list):  # Fixed
        """Metamorphoric Relation 7: Blocking a job and then unblocking it to a higher priority should not change the
        output if a FINISH operation follows, because the current (previously blocked) job will be removed."""
        job_list[0] = "0"
        job_list[1] = str(int(job_list[1]) + randint(1, 100))

        # Construct source input with initial conditions and perform BLOCK then UNBLOCK with different priority and FINISH
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op = SCHEDULE_OPERATIONS["BLOCK"] + "\n" + SCHEDULE_OPERATIONS["UNBLOCK"] + " 1\n" + SCHEDULE_OPERATIONS["UPGRADE_PRIO"] + " " + PRIORITY_LEVEL["MEDIUM"] + " 1\n" + SCHEDULE_OPERATIONS["FINISH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Construct follow-up input with initial conditions and perform FINISH
        follow_op = SCHEDULE_OPERATIONS["FINISH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The current process should be finished in both cases, resulting in the same output
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
