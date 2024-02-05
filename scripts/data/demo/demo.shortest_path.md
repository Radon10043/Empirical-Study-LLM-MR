```python
@parameterized.expand(load_test_cases)
def test1(self, graph: list, src: int, dst: int, method: str):
    """Metamorphic Relation 1: Given the same graph, the same source and destination vertices,
    but with different algorithms, the output should be the same."""
    # Get source output
    source_out = shortest_path(graph, method=method)[src][dst]

    # Construct follow-up input
    follow_method = "FW"
    if method == "FW":
        follow_method = "D"

    # Get folllow-up output
    follow_out = shortest_path(graph, method=follow_method)[src][dst]

    # Verification
    self.assertEqual(source_out, follow_out)

@parameterized.expand(load_test_cases)
def test2(self, graph: list, src: int, dst: int, method: str):
    """Metamorphic Relation 2: Given the same graph, the same source and destination vertices,
    but weights scaled 2 times, the output should also be scaled 2 times."""
    # Get source output
    source_out = shortest_path(graph, method=method)[src][dst]

    follow_graph = list()
    for row in graph:
        follow_graph.append([x * 2 for x in row])

    # Get folllow-up output
    follow_out = shortest_path(follow_graph, method)[src][dst]

    # Verification
    self.assertEqual(source_out * 2, follow_out)
```