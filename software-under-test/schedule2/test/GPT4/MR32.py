import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule2.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test32(self, job_list: list):  # Fixed
        """Metamorphic Relation 32: Executing the UPGRADE_PRIO operation on all jobs to the MAXPRIO, followed by a QUANTUM_EXPIRE,
        and then FINISH operation, should have the same result as performing a sequence of FINISH operations
        on the initial unmodified list of jobs, because all jobs are at the same priority level."""
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Upgrade all jobs to the maximum priority
        source_op = str()
        for _ in range(int(job_list[1])):
            source_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['MEDIUM']} 0.0\n"
        for _ in range(int(job_list[2])):
            source_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['LOW']} 0.0\n"
            source_op += f"{SCHEDULE_OPERATIONS['UPGRADE_PRIO']} {PRIORITY_LEVEL['MEDIUM']} 0.0\n"

        # Execute a QUANTUM_EXPIRE followed by FINISH on the max priority job
        source_op += SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"] + "\n"
        source_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]

        # Perform flush to capture output
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Perform a sequence of FINISH operations on initial unmodified jobs
        job_cnt = int(job_list[0]) + int(job_list[1]) + int(job_list[2])
        follow_op = str()
        for _ in range(job_cnt):
            follow_op += SCHEDULE_OPERATIONS["FINISH"] + "\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")

        # Verification: The output order after upgrades and expire/finish should match the order after a sequence of finishes
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
