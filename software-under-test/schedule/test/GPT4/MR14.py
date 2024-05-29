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
    def test14(self, job_list: list):
        """Metamorphic Relation 14: Flushing processes of a specific priority should leave processes of other priorities unaffected."""
        # Flush high priority processes, then flush all
        specific_then_all_flush_op = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['HIGH']}",
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}",
            f"{SCHEDULE_OPERATIONS['FLUSH']} {PRIORITY_LEVEL['HIGH']}",
            SCHEDULE_OPERATIONS['FLUSH']
        ]

        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        specific_then_all_flush_out = subprocess.check_output(cmd_list, input="\n".join(specific_then_all_flush_op), text=True).split()

        # Flush all processes
        all_flush_op = [
            f"{SCHEDULE_OPERATIONS['NEW_JOB']} {PRIORITY_LEVEL['MEDIUM']}",
            SCHEDULE_OPERATIONS['FLUSH']
        ]

        all_flush_out = subprocess.check_output(cmd_list, input="\n".join(all_flush_op), text=True).split()

        # Compare that only medium priority processes remain after a specific priority flush
        self.assertListEqual(specific_then_all_flush_out[1:], all_flush_out)


if __name__ == "__main__":
    unittest.main()
