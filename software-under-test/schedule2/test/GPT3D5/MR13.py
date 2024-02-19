from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule2.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    # Fix
    @parameterized.expand(load_test_cases(1000))
    def test_metamorphic_relation_13(self, job_list: list):
        """Metamorphic Relation 13: If a new job is added with a specific priority, the current process is finished, and then the scheduler state is flushed, it will have the same result as adding the new job and then flushing the scheduler state without finishing the process."""
        # Get source output
        source_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["HIGH"] + "\n" + SCHEDULE_OPERATIONS["FINISH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).replace("\n", "")

        # Construct follow-up input
        follow_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["HIGH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).replace("\n", "")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
