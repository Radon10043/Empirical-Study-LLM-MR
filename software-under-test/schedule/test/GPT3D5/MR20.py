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
    def test20(self, job_list: list):
        """Metamorphic Relation 20: If all jobs are blocked and then unblocked in ascending order of priority, the resulting output should remain consistent with the order of priority."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"], SCHEDULE_OPERATIONS["BLOCK"],
                    SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"], SCHEDULE_OPERATIONS["UNBLOCK"],
                    SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Verification
        assert source_out == subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")


if __name__ == "__main__":
    unittest.main()
