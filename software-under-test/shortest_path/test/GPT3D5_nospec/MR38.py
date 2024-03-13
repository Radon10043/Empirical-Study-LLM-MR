import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test38(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 38: Given the same graph and vertices, if all edge weights are set to zero,
        the shortest path length should be zero for all vertices to itself."""
        # Set all edge weights to zero
        zero_graph = [[0 for _ in row] for row in graph]

        for i in range(len(graph)):
            self.assertEqual(shortest_path(zero_graph, method=method)[i][i], 0)


if __name__ == "__main__":
    unittest.main()
