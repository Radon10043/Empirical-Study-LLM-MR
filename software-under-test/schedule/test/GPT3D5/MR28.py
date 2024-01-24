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
    def test28(self, job_list: list):
        """Metamorphic Relation 28: If two jobs with different priorities are added and then the operation of quantum expiration is performed, the resulting output should be the same as if the quantum expiration operation is performed first and then the jobs are added."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["LOW"],
                    SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input to perform the operation of quantum expiration first and then add the jobs
        follow_op = [SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"],
                    SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["LOW"], SCHEDULE_OPERATIONS["FLUSH"]]
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out == follow_out


if __name__ == "__main__":
    unittest.main()
