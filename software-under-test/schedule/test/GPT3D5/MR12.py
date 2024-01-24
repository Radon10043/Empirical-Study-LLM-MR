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
    def test12(self, job_list: list):
        """Metamorphic Relation 12: If the same sequence of operations is applied to two identical job lists, the resulting outputs should also be identical."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["LOW"], SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["MEDIUM"], SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Verification
        assert source_out == subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")


if __name__ == "__main__":
    unittest.main()
