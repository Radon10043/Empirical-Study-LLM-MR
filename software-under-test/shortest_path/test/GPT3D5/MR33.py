import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 33: Given the same graph, the same source and destination vertices,
        but with the graph where all edge weights are scaled by a factor, the shortest path should also be scaled by the same factor."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Scale all edge weights by a factor
        factor = 0.5
        follow_graph = [[x * factor for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out * factor, follow_out))


if __name__ == "__main__":
    unittest.main()
