import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test10(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 10: If the graph is augmented with a new node connected
        by edges with infinite weight, the shortest path should remain unchanged."""
        # Get source output for the original graph
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a new node connected by infinite weight edges
        num_nodes = len(graph)
        graph.append([float("inf")] * num_nodes)
        for row in graph:
            row.append(float("inf"))

        # Get follow-up output
        follow_out = shortest_path(graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
