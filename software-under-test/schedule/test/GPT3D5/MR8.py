from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    # Fix
    @parameterized.expand(load_test_cases(1000))
    def test8(self, job_list: list):
        """Metamorphic Relation 8: Blocking and unblocking a process has the same output as not performing any blocking or unblocking."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], "0", SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input
        follow_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
