# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of the program `tcas`. `tcas` is an aircraft collision avoidance system from Simens programs. Its inputs are 12 integers, include `Cur_Vertical_Sep`, `High_Confidence`, `Two_of_Three_Reports_Valid`, `Own_Tracked_Alt`, `Own_Tracked_Alt_Rate`, `Other_Tracked_Alt`, `Alt_Layer_Value`, `Up_Separation`, `Down_Separation`, `Other_RAC`, `Other_Capability`, and `Climb_Inhibit`. Its output is an integer indicating that the aircraft should climb(`1`), descend(`2`), or remain the current trajectory(`0`). Please identify the metamorphic relations of `tcas` as much as possible and codify them as Python code. Here are some examples:

```python
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

@parameterized.expand(load_test_cases)
def test1(self, vals: list):
    """Metamorphic Relation 1: If the relation of the Own_Tracked_Alt and Other_Tracked_Alt is not changed,
    meanwhile other parameter values are not changed too, then the outputs of the TCAS should be the same."""
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
    """Given that the intruder aircraft does not have the TCAS system, if we change the state that the intruder
    aircraft has an intention or not, the output should not change."""
    if vals[INDEX["Other_Capability"]] != OTHER_CAPABILITY_VALUES["TCAS_TA"]:
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
    """Metamorphic Relation 3: Given that the intruder aircraft does not have the TCAS system,
    if we change the state that the report describing the presence of any intruder is valid or
    not, the output should not change."""
    if vals[INDEX["Other_Capability"]] != OTHER_CAPABILITY_VALUES["TCAS_TA"]:
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
    """Given that the intruder aircraft does not have any intention, and the report describing the presence of
    any intruder is valid, if we change the state that the intruder aircraft has the TCAS system or not, the
    output should not change."""
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

## Chat 4...n

Please identify more different metamorphic relations of this program and codify them as Python code.