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
    def test11(self, job_list: list):
        """Metamorphic Relation 11: If all jobs are blocked and then unblocked, the resulting output should be the same as the original output."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Verification
        assert source_out == subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")


if __name__ == "__main__":
    unittest.main()
