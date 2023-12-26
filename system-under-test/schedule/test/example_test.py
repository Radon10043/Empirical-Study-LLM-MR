import unittest
import os, subprocess, time

from parameterized import parameterized


# ==================== GLOBAL VRAIABLES ====================
SCHEDULE_PATH = os.path.join(os.path.dirname(__file__), "..", "src", "schedule.out")

# fmt:off
SCHEDULE_OPERATIONS = {
    "NEW_JOB"       : "1",
    "UPGRADE_PRIO"  : "2",
    "BLOCK"         : "3",
    "UNBLOCK"       : "4",
    "QUANTUM_EXPIRE": "5",
    "FINISH"        : "6",
    "FLUSH"         : "7"
}

PRIORITY_LEVEL = {
    "HIGH"  : "3",
    "MEDIUM": "2",
    "LOW"   : "1"
}
# fmt:on
# ==========================================================


def load_test_cases() -> list:
    """读取所有测试用例

    Returns
    -------
    list
        存储测试用例的列表
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    tcs = list()

    # 遍历存储测试用例的根目录, 依次读取文件
    for file in os.listdir(tcs_dir):
        with open(os.path.join(tcs_dir, file), "r") as f:
            tcs.append((f.read().split(),))

    return tcs


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test1(self, job_list: list):
        """Metamorphic Relation 1: If the size of a job-list is 1, then the operation that moving the job at the top of this list to the end will not affect the output.

        Parameters
        ----------
        job_list : list
            _description_
        """
        if int(job_list[2]) != 1:
            return

        # Get source output
        source_op = [SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input
        follow_op = [SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test2(self, job_list: list):
        """Metamorphic Relation 2: Two different sets of operations: The first is adding one job at the end of the
        queue with high priority, while the second is adding one job at the end of the queue with medium priority,
        and then moving it to the queue with high priority. They will output the same.

        Parameters
        ----------
        job_list : list
            _description_
        """
        # Get source output
        source_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["HIGH"], SCHEDULE_OPERATIONS["FLUSH"]]
        cmd_list = [SCHEDULE_PATH]
        cmd_list.extend(job_list)
        source_out = subprocess.check_output(cmd_list, input=" ".join(source_op), text=True).split("\n")

        # Construct follow-up input
        follow_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["MEDIUM"], SCHEDULE_OPERATIONS["UPGRADE_PRIO"], PRIORITY_LEVEL["MEDIUM"], "0.99999", SCHEDULE_OPERATIONS["FLUSH"]]

        # Get follow-up output
        follow_out = subprocess.check_output(cmd_list, input=" ".join(follow_op), text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
