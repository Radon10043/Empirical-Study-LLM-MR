import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test14(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 14: Introducing a new start node with zero weight edges to all other nodes should
        not change the shortest path from the original source to destination."""
        # Get source output
        original_cost = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up graph with an additional node 'new_src' connected to all nodes including 'src' with zero weight
        new_src = len(graph)
        for row in graph:
            row.append(0)  # Connect new_src with zero weight to all other nodes
        graph.append([0] * (new_src + 1))  # Connect all other nodes with zero weight to new_src

        # New source is the last node added
        follow_up_cost = shortest_path(graph, method=method)[src][dst]

        # Verification
        self.assertEqual(original_cost, follow_up_cost)


if __name__ == "__main__":
    unittest.main()
