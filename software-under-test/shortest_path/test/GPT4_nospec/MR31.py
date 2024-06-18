import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test31(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 31: Scaling the weights of edges by a negative factor should not be used, as it violates the assumption of non-negative edges, but if done, should invalidate the original shortest path."""
        # Attempt to scale the weights of the graph by a negative factor; this is typically not a valid operation
        # This test assumes that the shortest_path function will raise an exception or return a specific error value when presented with an invalid graph

        # Scale the weights by a negative factor
        invalid_graph = [[-weight for weight in row] for row in graph]

        # Verify that shortest_path function properly handles this invalid input
        with self.assertRaises(ValueError):
            shortest_path(invalid_upsidedown_graph, method=method)


if __name__ == "__main__":
    unittest.main()
