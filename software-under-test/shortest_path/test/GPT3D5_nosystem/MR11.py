import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test11(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 11: Given the same graph and the same source and destination vertices,
        if the graph is transformed into a different graph by adding or removing edges,
        the shortest path results should be impacted accordingly."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Construct follow-up input by adding or removing edges
        num_v = len(graph)
        modified_graph = graph.copy()
        modified_graph.append([0] * num_v)
        for i in range(num_v):
            modified_graph[i].append(0)

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
