import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: Given the same graph with negative weights, the result should remain the same if all weights are shifted by adding a large positive constant K."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Shift all weights by adding a large positive constant K
        constant_k = 1000
        follow_graph = [[x + constant_k for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
