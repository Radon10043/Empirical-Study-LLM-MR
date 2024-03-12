import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def remove_edge_between_nodes(self, graph: list, src: int, dst: int) -> list:
        """Remove an edge between two existing nodes in the graph.

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
            The new graph after removing an edge between two existing nodes
        """
        inf = 99999
        new_graph = [row[:] for row in graph]
        new_graph[src][dst] = inf
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 25: If the graph represents a transportation network, removing an edge between two existing nodes should change the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Remove an edge between two existing nodes
        new_graph = self.remove_edge_between_nodes(graph, src, dst)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that the distance has changed
        self.assertNotEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == "__main__":
    unittest.main()
