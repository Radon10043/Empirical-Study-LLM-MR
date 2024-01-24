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
    def test15(self, job_list: list):
        """Metamorphic Relation 15: If all jobs are finished and then a new job with high priority is added, the resulting output should be the same as if the new job was added first and then all jobs were finished."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"],
                    SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input where a new job with high priority is added before finishing all jobs
        follow_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out == follow_out


if __name__ == "__main__":
    unittest.main()
