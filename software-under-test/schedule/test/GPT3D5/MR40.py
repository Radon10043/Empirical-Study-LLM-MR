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
    def test40(self, job_list: list):
        """Metamorphic Relation 40: If a new job with high priority is added, and then all jobs are blocked, the resulting output should be different from the original output."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"],
                    SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], 
                    SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input to block all jobs after adding a new job with high priority
        follow_op = [SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], 
                    SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out != follow_out


if __name__ == "__main__":
    unittest.main()