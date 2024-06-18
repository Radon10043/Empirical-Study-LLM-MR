import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 27: Adding a new node that has edges with zero weight to all other nodes should not change
        the shortest path length from src to dst."""
        # Get the current shortest path weight
        shortest_path_cost = shortest_path(graph, method=method)[src][dst]

        # Add a new node with zero-weight edges to all other nodes
        new_node_index = len(graph)
        graph.append([0] * new_node_index)  # Zero-weight edges from new node
        for row in graph:
            row.append(0)  # Zero-weight edges to new node

        # Verify the shortest path cost doesn't change after adding the new zero-weight node
        new_shortest_path_cost = shortest_path(graph, method=method)[src][dst]
        self.assertEqual(shortest_path_cost, new_shortest_path_cost)


if __name__ == "__main__":
    unittest.main()
