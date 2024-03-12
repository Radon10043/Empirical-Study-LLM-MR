import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):

    def add_edge(self, graph: list, weight: int, src: int, dst: int) -> list:
        """Add an edge to the graph between two nodes.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        weight : int
            The weight of the new edge
        src : int
            The source node
        dst : int
            The destination node

        Returns
        -------
        list
            The new graph after adding the edge
        """
        graph[src][dst] = weight
        return graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 13: If an edge is added to the graph between two nodes, the shortest path between these two nodes should decrease or stay the same."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=False)[src][dst]

        # Add an edge between two nodes
        new_edge_weight = random.randint(1, 1000)
        follow_graph = self.add_edge(graph, new_edge_weight, src, dst)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method, directed=False)[src][dst]

        # Verification
        self.assertLessEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()