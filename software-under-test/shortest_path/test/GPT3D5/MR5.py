import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test5(self, graph: list, src: int, dst: int, method: str):  # Fixed
        """Metamorphic Relation 5: Given the same graph, the same source and destination vertices,
        but ignoring the last two vertices, the output should remain the same for the first n-2 vertices."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        follow_graph = [row[:-2] for row in graph[:-2]]
        follow_out = shortest_path(follow_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out[:-2, :-2], follow_out))


if __name__ == "__main__":
    unittest.main()
