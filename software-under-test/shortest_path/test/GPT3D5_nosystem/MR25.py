import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test25(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 25: Given the same graph, the same source and destination vertices,
        if all edge weights are multiplied by a constant, the shortest path lengths should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Create a new graph with all edge weights multiplied by a constant
        modified_graph = [[x * 2 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
