from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule2.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test14(self, job_list: list):
        """Metamorphic Relation 14: If the job list is modified by reordering jobs within the same priority level, the execution order remains unchanged."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split("\n")

        # Modify the job list by reordering jobs within the same priority level
        modified_job_list = [job_list[0], job_list[2], job_list[1]]

        # Get follow-up output with modified job list
        follow_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
