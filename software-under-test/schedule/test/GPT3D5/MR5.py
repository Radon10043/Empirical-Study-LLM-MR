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
    def test5(self, job_list: list):
        """Metamorphic Relation 5: If the order of the job list is reversed, the resulting output should also be reversed."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Reverse the job list
        reversed_job_list = list(reversed(job_list))

        # Get follow-up output with the reversed job list
        follow_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Verification
        assert source_out == list(reversed(follow_out))


if __name__ == "__main__":
    unittest.main()
