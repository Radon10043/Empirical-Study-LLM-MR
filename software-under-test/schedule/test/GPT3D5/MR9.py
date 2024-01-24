from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test9(self, job_list: list):
        """Metamorphic Relation 9: If the job list is unchanged, the resulting output should remain the same regardless of any operations."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input with various operations
        follow_op = [SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["MEDIUM"], SCHEDULE_OPERATIONS["UPGRADE_PRIO"], PRIORITY_LEVEL["MEDIUM"], "0.99999", SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out == follow_out


if __name__ == "__main__":
    unittest.main()
