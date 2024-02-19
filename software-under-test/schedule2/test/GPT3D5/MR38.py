from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule2.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    # Fixed
    @parameterized.expand(load_test_cases(1000))
    def test_metamorphic_relation_38(self, job_list: list):
        """Metamorphic Relation 38: The result of adding a new job with a specific priority into an empty scheduler followed by expiring the quantum for the current process will be the same as adding the new job and then expiring the quantum for the process."""
        # job_list = ["0", "0", "0"]
        for i in range(3):
            if job_list[i] != "0":
                self.skipTest("This test case is not applicable for the current job list.")

        # Get source output
        source_op = SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["HIGH"] + "\n" + SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Construct follow-up input
        follow_op = SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n" + SCHEDULE_OPERATIONS["NEW_JOB"] + " " + PRIORITY_LEVEL["HIGH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
