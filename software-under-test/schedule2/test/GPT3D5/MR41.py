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
    def test41(self, job_list: list):
        """Metamorphic Relation 41: If a new job is added to the front of the queue and then all jobs are upgraded to a higher priority, the execution order reflects the priority change."""
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["UPGRADE_PRIO"], PRIORITY_LEVEL["HIGH"]] * len(job_list) + [SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split("\n")

        # Construct follow-up input
        follow_up_op = [SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_up_out = subprocess.check_output(cmd_list, input="\n".join(follow_up_op), text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_up_out)


if __name__ == "__main__":
    unittest.main()
