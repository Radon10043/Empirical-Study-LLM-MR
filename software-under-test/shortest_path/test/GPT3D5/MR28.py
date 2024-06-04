import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test28(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 28: Given the same graph, the same source and destination vertices,
        but with all edge weights set to zero, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify graph by setting all edge weights to zero
        follow_graph = [[0 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
