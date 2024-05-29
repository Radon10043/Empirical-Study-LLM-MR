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
    def test3(self, job_list: list):    # Fixed
        """Metamorphic Relation 3: Flushing twice will lead to the same output, irrespective of the order of processes,
        since all processes will be terminated."""
        # Construct source input with initial conditions and perform FLUSH
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_op = SCHEDULE_OPERATIONS["FLUSH"]
        source_out = subprocess.check_output(cmd_list, input=source_op, text=True).split("\n")

        # Construct follow-up input, repeat FLUSH
        follow_op = SCHEDULE_OPERATIONS["FLUSH"] + "\n" + SCHEDULE_OPERATIONS["FLUSH"]
        # No need for initial_conditions as they were flushed by the source operation
        follow_out = subprocess.check_output(cmd_list, input=follow_op, text=True).split("\n")
        follow_out.pop()

        # Verification: Both operations should produce empty outputs
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
