import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test36(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 36: Given the same graph and vertices, if the weights of all edges are randomized,
        the shortest path should still conform to the shortest path property."""
        import random

        # Get the original shortest path
        original_shortest_path = shortest_path(graph, method=method)[src][dst]

        # Randomize the weights in the graph
        random_graph = [[random.randint(1, 100) for _ in range(len(graph))] for _ in range(len(graph))]

        # Get the shortest path in the randomized graph
        random_shortest_path = shortest_path(random_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(random_shortest_path >= original_shortest_path)


if __name__ == "__main__":
    unittest.main()
