```python
@parameterized.expand(load_test_cases)
def test1(self, job_list: list):
    """Metamorphic Relation 1: If the size of a job-list is 1, then the operation that moving the job at the top of this list to the end will not affect the output."""
    high_priority_index = int(PRIORITY_LEVEL["HIGH"]) - 1
    if int(job_list[high_priority_index]) != 1:
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
    and then moving it to the queue with high priority. They will output the same."""
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
```