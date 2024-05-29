import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build schedule.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test26(self, job_list: list):
        """
        Expire the quantum of two different jobs and verify if
        the state and output remain consistent with the order in which
        quantum expiration was invoked.
        """
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)

        # Add two new jobs with different priorities and trigger quantum expiration for each
        ops_sequence_1 = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

        output_sequence_1 = subprocess.check_output(cmd_list, input="\n".join(ops_sequence_1), text=True).strip()

        # Add the same jobs but trigger quantum expiration in reverse order
        ops_sequence_2 = [f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['LOW']}", f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}", SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

        output_sequence_2 = subprocess.check_output(cmd_list, input="\n".join(ops_sequence_2), text=True).strip()

        # Verify that order of quantum expirations does not affect the final state/output of processes
        self.assertEqual(output_sequence_1, output_sequence_2)


if __name__ == "__main__":
    unittest.main()
