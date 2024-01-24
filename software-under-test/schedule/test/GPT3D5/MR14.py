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
    def test14(self, job_list: list):
        """Metamorphic Relation 14: If all jobs are blocked and a job is finished, and then all jobs are unblocked, the resulting output should be the same as if all jobs were unblocked first, and then a job was finished."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input where a job is finished before unblocking all jobs
        follow_op = [SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["FINISH"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out == follow_out


if __name__ == "__main__":
    unittest.main()
