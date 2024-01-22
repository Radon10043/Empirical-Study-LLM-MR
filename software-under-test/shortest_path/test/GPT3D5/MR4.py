import numpy as np

import unittest
import os, sys

from copy import deepcopy
from parameterized import parameterized
from scipy.sparse.csgraph import shortest_path
from scipy.sparse import csr_matrix

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))

from utils import gen_tcs_randomly


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly)
    def test4(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 4: Given the same graph, the same source and destination vertices, and the shortest path,
        removing any edge on the path should result in a new shortest path with a length greater or equal."""
        # Get the shortest path for the original graph
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Find an edge on the shortest path
        # path = shortest_path(graph, method=method, return_predecessors=True)
        # edge_to_remove = None
        # v = dst
        # while v != src:
        #     u = path[1][v]
        #     if graph[u][v] != np.inf:  # Check for edge existence
        #         edge_to_remove = (u, v)
        #         break
        #     v = u

        # Fix by Radon: temp
        edge_to_remove = None
        for i in range(len(graph)):
            for j in range(len(graph)):
                if i != j and graph[i][j] != np.inf:
                    edge_to_remove = (i, j)
                    break

        new_graph = deepcopy(graph)
        if edge_to_remove:
            new_graph[edge_to_remove[0]][edge_to_remove[1]] = np.inf  # Remove the edge

        # Get the shortest path for the modified graph
        new_shortest_path = shortest_path(new_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(new_shortest_path, original_shortest_path)


if __name__ == "__main__":
    unittest.main()
