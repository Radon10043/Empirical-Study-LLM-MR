import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test29(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 29: Given the same graph, the same source and destination vertices,
        but with all edge weights incremented by a constant C, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Increment all edge weights by a constant C
        constant_c = 5
        follow_graph = [[x + constant_c for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
