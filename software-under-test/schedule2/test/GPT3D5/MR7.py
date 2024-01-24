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
    def test7(self, job_list: list):
        """Metamorphic Relation 7: If the job list is modified by adding or removing a job, the execution order remains consistent."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split("\n")

        # Construct follow-up input with one job removed
        follow_op_remove = [SCHEDULE_OPERATIONS["FLUSH"]]
        modified_job_list_remove = job_list[:-1]

        # Get follow-up output with one job removed
        follow_out_remove = subprocess.check_output(cmd_list, input="\n".join(follow_op_remove), text=True).split("\n")

        # Verification for job removal
        self.assertEqual(source_out, follow_out_remove)

        # Construct follow-up input with one job added
        follow_op_add = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["MEDIUM"], SCHEDULE_OPERATIONS["FLUSH"]]
        modified_job_list_add = job_list + [PRIORITY_LEVEL["MEDIUM"]]

        # Get follow-up output with one job added
        follow_out_add = subprocess.check_output(cmd_list, input="\n".join(follow_op_add), text=True).split("\n")

        # Verification for job addition
        self.assertEqual(source_out, follow_out_add)


if __name__ == "__main__":
    unittest.main()
