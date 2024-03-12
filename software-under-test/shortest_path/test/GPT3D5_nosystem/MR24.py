import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def add_edge_between_nodes(self, graph: list, src: int, dst: int) -> list:
        """Add a new edge between two existing nodes in the graph.

        Parameters
        ----------
        graph : list
            The adjacency matrix of the graph
        src : int
            The source vertex
        dst : int
            The destination vertex

        Returns
        -------
        list
            The new graph after adding a new edge between two existing nodes
        """
        new_graph = [row[:] for row in graph]
        new_graph[src][dst] = random.randint(1, 1000)
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 24: If the graph represents a transportation network, adding a new edge between two existing nodes should change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Add a new edge between two existing nodes
        new_graph = self.add_edge_between_nodes(graph, src, dst)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that the distance has changed
        self.assertNotEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == "__main__":
    unittest.main()