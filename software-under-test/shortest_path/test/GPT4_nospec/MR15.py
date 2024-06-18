import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test15(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 15: Adding a node with only infinite weight connections should not affect the shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a new node with infinite weight connections
        num_nodes = len(graph)
        graph.append([float("inf")] * num_nodes)  # Infinite weights to existing nodes
        for row in graph:
            row.append(float("inf"))  # Infinite weights from existing nodes

        # Get follow-up output
        follow_out = shortest_path(graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
