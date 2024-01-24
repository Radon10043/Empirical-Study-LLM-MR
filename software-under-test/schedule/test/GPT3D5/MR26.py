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
    def test26(self, job_list: list):
        """Metamorphic Relation 26: If a new job with the highest priority is added and then all jobs are unblocked, the resulting output should be the same as if the jobs were unblocked first and then the new job was added."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["UNBLOCK"], 
                    SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input to unblock all jobs first and then add the new job
        follow_op = [SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], 
                    SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out == follow_out


if __name__ == "__main__":
    unittest.main()
