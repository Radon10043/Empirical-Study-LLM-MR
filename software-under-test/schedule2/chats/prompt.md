# Prompt

## Chat 1

Metamorphic testing is usually used to check whether the software under test satisfies specific properties. Among them, metamorphic relation is the core concept of metamorphic testing. The metamorphic relation can be considered a formal expression of the properties of the software under test and usually consists of two parts, namely the input relation and the output relation.

## Chat 2

For the function $sin(x)$, assuming there is an origin input $x1$, the corresponding origin output is $y1$, $x2$ is a follow-up input, and the corresponding follow-up output is $y2$. $x2$ is transformed from $x1$, and there is an input relation between $x2$ and $x1$: $x2=\pi-x1$, an output relation between $y1$ and $y2$: $y1=y2$. Therefore, there is a metamorphic relation $sin(x)=sin(\pi-x)$.

## Chat 3

You are an expert on metamorphic testing. Based on the above case, please identify the metamorphic relation of the program `schedule2`. `schedule2` is a priority scheduler from Simens programs. Its inputs are three priority job-lists $P_1, P_2, and P_3$ with priorities: $P_3>P_2>P_1$, and a set of operations on jobs. Its output is execution order of the jobs. Please identify the metamorphic relations of `schedule2` as much as possible and codify them as Python code. Here are some examples:

```python
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
    "HIGH"  : "1",
    "MEDIUM": "2",
    "LOW"   : "3"
}

@parameterized.expand(load_test_cases)
def test1(self, job_list: list):
    """Metamorphic Relation 1: If the size of a job-list is 1, then the operation that moving the job at the top of this list to the end will not affect the output.

    Parameters
    ----------
    job_list : list
        _description_
    """
    high_priority_index = int(PRIORITY_LEVEL["HIGH"]) - 1
    if int(job_list[high_priority_index]) != 1:
        return

    # Get source output
    source_op = [SCHEDULE_OPERATIONS["FLUSH"]]
    cmd_list = [SCHEDULE_PATH]
    cmd_list.extend(job_list)
    source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split("\n")

    # Construct follow-up input
    follow_op = [SCHEDULE_OPERATIONS["QUANTUM_EXPIRE"], SCHEDULE_OPERATIONS["FLUSH"]]

    # Get follow-up output
    follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split("\n")

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
    source_out = subprocess.check_output(cmd_list, input="\n".join(source_op), text=True).split("\n")

    # Construct follow-up input
    follow_op = [SCHEDULE_OPERATIONS["NEW_JOB"], PRIORITY_LEVEL["MEDIUM"], SCHEDULE_OPERATIONS["UPGRADE_PRIO"], PRIORITY_LEVEL["MEDIUM"], "0.99999", SCHEDULE_OPERATIONS["FLUSH"]]

    # Get follow-up output
    follow_out = subprocess.check_output(cmd_list, input="\n".join(follow_op), text=True).split("\n")

    # Verification
    self.assertEqual(source_out, follow_out)
```

## Chat 4...n

Please identify more different metamorphic relations of this program and codify them as Python code.