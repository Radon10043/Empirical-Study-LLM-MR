import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test11(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 11: Given the same graph, the same source and destination vertices, 
        but with the weights randomized, the output should still satisfy the shortest path property."""
        import random

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Randomize the weights in the graph
        random_graph = [[random.randint(1, 100) for _ in range(len(graph))] for _ in range(len(graph))]

        # Get follow-up output
        follow_out = shortest_path(random_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(follow_out >= source_out)


if __name__ == "__main__":
    unittest.main()
