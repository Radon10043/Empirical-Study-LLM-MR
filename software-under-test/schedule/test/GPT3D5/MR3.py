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
    def test3(self, job_list: list):
        """Metamorphic Relation 3: If an operation changes the priority of a job, the resulting output should be different from the original output."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input to change the priority of a job
        follow_op = [SCHEDULE_OPERATIONS["UPGRADE_PRIO"], PRIORITY_LEVEL["MEDIUM"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        assert source_out != follow_out


if __name__ == "__main__":
    unittest.main()
