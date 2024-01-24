import unittest
import os, subprocess

from parameterized import parameterized


# ==================== GLOBAL VRAIABLES ====================
TCAS_PATH = os.path.join(os.path.dirname(__file__), "..", "src", "tcas.out")

# fmt:off
INDEX = {
    "Cur_Vertical_Sep"          : 0,
    "High_Confidence"           : 1,
    "Two_of_Three_Reports_Valid": 2,
    "Own_Tracked_Alt"           : 3,
    "Own_Tracked_Alt_Rate"      : 4,
    "Other_Tracked_Alt"         : 5,
    "Alt_Layer_Value"           : 6,
    "Up_Separation"             : 7,
    "Down_Separation"           : 8,
    "Other_RAC"                 : 9,
    "Other_Capability"          : 10,
    "Climb_Inhibit"             : 11
}

OTHER_RAC_VALUES = {
    "NO_INTENT"     : 0,
    "DO_NOT_CLIMB"  : 1,
    "DO_NOT_DESCEND": 2
}

OTHER_CAPABILITY_VALUES = {
    "TCAS_TA"       : 1,
    "OTHER"         : 2
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

    if not os.path.exists(tcs_dir):
        print("Oops, no testcases? Please run generate.py first!")
        exit(1)

    # 遍历存储测试用例的根目录, 依次读取文件
    for file in os.listdir(tcs_dir):
        with open(os.path.join(tcs_dir, file), "r") as f:
            lst = [int(x) for x in f.read().split()]
            tcs.append((lst,))

    return tcs


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test1(self, vals: list):
        """Metamorphic Relation 1: If the relation of the Own_Tracked_Alt and Other_Tracked_Alt is not changed, meanwhile other parameter values are not changed too, then the outputs of the TCAS should be the same."""
        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Own_Tracked_Alt"]] *= 2
        follow_vals[INDEX["Other_Tracked_Alt"]] *= 2

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test2(self, vals: list):
        """Meatmorphic Relation 2: Given that the intruder aircraft does not have the TCAS system, if we change the state that the intruder aircraft has an intention or not, the output should not change."""
        if vals[INDEX["Other_Capability"]] != OTHER_CAPABILITY_VALUES["OTHER"]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Other_RAC"]] = (follow_vals[INDEX["Other_RAC"]] + 1) % len(OTHER_RAC_VALUES)

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test3(self, vals: list):
        """Metamorphic Relation 3: Given that the intruder aircraft does not have the TCAS system, if we change the state that the report describing the presence of any intruder is valid or not, the output should not change."""
        if vals[INDEX["Other_Capability"]] != OTHER_CAPABILITY_VALUES["OTHER"]:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        if follow_vals[INDEX["Two_of_Three_Reports_Valid"]] != 0:
            follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = 0
        else:
            follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test4(self, vals: list):
        """Metamorphic Relation 4: Given that the intruder aircraft does not have any intention, and the report describing the presence of any intruder is valid, if we change the state that the intruder aircraft has the TCAS system or not, the output should not change."""
        if vals[INDEX["Other_RAC"]] != 0 or vals[INDEX["Two_of_Three_Reports_Valid"]] != 1:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Construct follow-up input
        follow_vals = vals.copy()
        if follow_vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["OTHER"]:
            follow_vals[INDEX["Other_Capability"]] = OTHER_CAPABILITY_VALUES["TCAS_TA"]
        else:
            follow_vals[INDEX["Other_Capability"]] = OTHER_CAPABILITY_VALUES["OTHER"]

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
