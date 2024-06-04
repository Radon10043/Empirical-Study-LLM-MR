import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test18(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 18: Given the same graph, the same source and destination vertices,
        but all edge weights multiplied by a constant factor, the shortest path lengths should also be multiplied by the same constant factor."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Multiply all edge weights by a constant factor
        factor = 2
        follow_graph = [[x * factor for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out*factor, follow_out))


if __name__ == "__main__":
    unittest.main()
