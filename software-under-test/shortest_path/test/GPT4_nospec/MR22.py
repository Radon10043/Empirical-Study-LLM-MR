import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 22: Adding a new edge with zero weight should not increase the cost 
        of the shortest path."""
        # Get the current shortest path weight
        shortest_path_cost = shortest_path(graph, method=method)[src][dst]

        # Add a new edge with zero weight between two random non-adjacent nodes
        new_zero_weight = 0
        non_adjacent_nodes = find_non_adjacent_nodes(graph) # Assuming this function exists
        if non_adjacent_nodes:
            node_a, node_b = non_adjacent_nodes
            add_edge(graph, node_a, node_b, new_zero_weight)  # Assuming 'add_edge' adds or updates the edge weight

            # Get the new shortest path and weight
            new_path_cost = shortest_path(graph, method=method)[src][dst]

            # The new shortest path cost should be less than or equal to the old one
            self.assertLessEqual(new_path_cost, shortest_path_cost)


if __name__ == "__main__":
    unittest.main()
