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
    def test22(self, job_list: list):
        """Metamorphic Relation 22: If a process's quantum expires and it is subsequently finished, the output should reflect the finishing of that process."""
        # Add a job, let its quantum expire and then finish it
        quantum_then_finish_ops = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            SCHEDULE_OPERATIONS['QUANTUM_EXPIRE'],
            SCHEDULE_OPERATIONS['FINISH'],
            SCHEDULE_OPERATIONS['FLUSH']
        ]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        quantum_then_finish_out = subprocess.check_output(cmd_list, input="\n".join(quantum_then_finish_ops), text=True).split()

        # Add a job and then just finish it without quantum expiration
        add_then_finish_ops = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            SCHEDULE_OPERATIONS['FINISH'],
            SCHEDULE_OPERATIONS['FLUSH']
        ]

        add_then_finish_out = subprocess.check_output(cmd_list, input="\n".join(add_then_finish_ops), text=True).split()

        # Verify that finishing after quantum expiration leads to the same termination ID as just finishing
        self.assertEqual(quantum_then_finish_out[0], add_then_finish_out[0])


if __name__ == "__main__":
    unittest.main()
