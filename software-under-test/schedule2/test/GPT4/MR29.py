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
    def test29(self, job_list: dict):   # Fixed
        """Metamorphic Relation 29: When a set of processes is added to the scheduling queue with distinct priorities
        and the system is flushed, adding the same set of processes in reverse priority order followed by a flush should
        produce the reversed order of process IDs."""
        # Add processes with ascending priorities and perform FLUSH
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op = str()
        for priority in [1, 2, 3]:
            source_op += f"{SCHEDULE_OPERATIONS['NEW_JOB']} {priority}\n"
        source_op += SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Add processes with descending priorities and perform FLUSH
        follow_op = str()
        for priority in reversed([1, 2, 3]):
            follow_op += f"{SCHEDULE_OPERATIONS['NEW_JOB']} {priority}\n"
        follow_op += SCHEDULE_OPERATIONS["FLUSH"]
        descending_flush_output = subprocess.check_output(cmd_list, input=follow_op, text=True).split()

        # Verification: The FLUSH output of descending priorities should be the reverse of ascending priorities
        self.assertEqual(source_out, list(reversed(descending_flush_output)))


if __name__ == "__main__":
    unittest.main()
