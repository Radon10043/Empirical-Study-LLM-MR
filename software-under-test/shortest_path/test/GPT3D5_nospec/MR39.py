import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test39(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 39: Given the same graph and vertices, if all edge weights are set to infinity, 
        the shortest path between any pair of vertices should also be infinity."""
        # Set all edge weights to infinity
        inf_graph = [[float('inf') for _ in row] for row in graph]

        for i in range(len(graph)):
            for j in range(len(graph)):
                self.assertEqual(shortest_path(inf_graph, method=method)[i][j], float('inf'))


if __name__ == "__main__":
    unittest.main()
