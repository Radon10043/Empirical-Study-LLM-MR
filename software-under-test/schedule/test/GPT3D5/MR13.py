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
    def test13(self, job_list: list):
        """Metamorphic Relation 13: If all jobs are finished in a certain order, and then another job is added, the resulting output should not be affected by the addition of the new job."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"],
                    SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input to add a new job after finishing all jobs
        follow_op = [SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"],
                    SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out == follow_out


if __name__ == "__main__":
    unittest.main()