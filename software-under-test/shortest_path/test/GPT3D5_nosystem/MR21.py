import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    def disconnect_nodes(self, graph: list, src: int, dst: int) -> list:
        """Disconnect two nodes in the graph by setting the edge weight to infinity or removing the edge.

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
            The new graph after disconnecting the nodes
        """
        inf = 99999
        new_graph = [row[:] for row in graph]
        new_graph[src][dst] = inf
        return new_graph

    @parameterized.expand(gen_tcs_randomly(1000))
    def test21(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 21: For any two nodes A and B, disconnecting node A and node B (by setting the edge weight to infinity or removing the edge) should affect the shortest path distances."""
        # Get source output
        source_out = shortest_path(graph, method=method, directed=True)

        # Disconnect node A and node B
        new_graph = self.disconnect_nodes(graph, src, dst)

        # Get follow-up output
        follow_out = shortest_path(new_graph, method=method, directed=True)

        # Verify that the distance has changed
        self.assertNotEqual(source_out[src][dst], follow_out[src][dst])


if __name__ == "__main__":
    unittest.main()
