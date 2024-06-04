import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test27(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 27: Given the same graph, the same source and destination vertices,
        but with all edge weights set to the same value, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Modify graph by setting all edge weights to the same value
        constant_value = 10
        follow_graph = [[constant_value for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
