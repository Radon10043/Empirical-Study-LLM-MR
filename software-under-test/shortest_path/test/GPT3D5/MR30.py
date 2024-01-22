import unittest
import os, sys

from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: Given the same graph, the same source and destination vertices,
        if we add a negative weight to an existing edge on the shortest path, the shortest path length should remain unchanged."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Find an edge on the shortest path
        shortest_path_detail = shortest_path(graph, method=method, return_predecessors=True)
        edge_to_modify = None
        v = dst
        while v != src:
            u = shortest_path_detail[1][v]
            if graph[u][v] != np.inf:  # Check for edge existence
                edge_to_modify = (u, v)
                break
            v = u

        if edge_to_modify:
            # Add a negative weight to the edge on the shortest path
            modified_graph = deepcopy(graph)
            modified_graph[edge_to_modify[0]][edge_to_modify[1]] -= 1  # Add a negative weight

            # Get the shortest path for the modified graph
            modified_shortest_path = shortest_path(modified_graph, method=method)[src][dst]

            # Verification
            self.assertEqual(original_shortest_path, modified_shortest_path)


if __name__ == "__main__":
    unittest.main()
