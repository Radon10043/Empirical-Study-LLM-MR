import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test34(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 34: For a connected graph, adding an edge with the maximum possible weight
        (max_edge_weight) should not create a new shortest path if the src and dst are the same."""
        # Get the current shortest path weight
        shortest_path_cost = shortest_path(graph, method=method)[src][dst]

        # Maximum possible weight could be based on the system's max size, or a large number to simulate 'infinity'
        # For this example, we use a large value to represent max_edge_weight
        max_edge_weight = float("inf")

        # Add an edge (src,dst) with the maximum weight, without changing other weights
        graph_with_max_edge = deepcopy(graph)
        for i in range(len(graph_with_max_edge)):
            for j in range(len(graph_with_max_edge)):
                if i != j and graph_with_max_edge[i][j] == 0:
                    graph_with_max_edge[i][j] = max_edge_weight

        # Get the shortest path weight after adding the maximum weight edge
        new_shortest_path_cost = shortest_path(graph_with_max_edge, method=method)[src][dst]

        # Verification: Adding a maximum weight edge should not change the shortest path from src to dst
        self.assertEqual(shortest_path_cost, new_shortest_path_cost)


if __name__ == "__main__":
    unittest.main()
