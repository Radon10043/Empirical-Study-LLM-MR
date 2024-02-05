```python
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
```