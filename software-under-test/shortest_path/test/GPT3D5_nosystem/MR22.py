import os, sys
import random

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test22(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 22: Given the same graph, the same source and destination vertices,
        if the graph is empty, the shortest path length should also be 0 for all vertices."""
        # Construct an empty graph
        empty_graph = [[np.inf if i != j else 0 for j in range(len(graph))] for i in range(len(graph))]

        # Get source output with the empty graph
        source_out_empty = shortest_path(empty_graph, method=method)

        # Verify that the shortest path length is 0 for all vertices
        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(source_out_empty[i][j], 0)


if __name__ == "__main__":
    unittest.main()
