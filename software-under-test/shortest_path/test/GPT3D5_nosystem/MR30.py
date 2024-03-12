import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def find_min_edge_weight(self, graph: list) -> int:
        """Find the minimum edge weight in the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph

        Returns
        -------
        int
            The minimum edge weight in the graph
        """
        min_edge_weight = float("inf")
        for row in graph:
            for weight in row:
                if weight != 0 and weight < min_edge_weight:
                    min_edge_weight = weight
        return min_edge_weight

    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 30: For any two nodes A and B, the shortest path from node A to node B should be greater than or equal to the weight of any edge in the graph."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Find the minimum edge weight in the graph
        min_edge_weight = self.find_min_edge_weight(graph)

        # Verify that the distance from A to B is greater than or equal to the minimum edge weight
        self.assertGreaterEqual(source_out[src][dst], min_edge_weight)


if __name__ == "__main__":
    unittest.main()
