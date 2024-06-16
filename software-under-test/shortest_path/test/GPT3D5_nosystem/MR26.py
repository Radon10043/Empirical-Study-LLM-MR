import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 26: Given the same graph and the same source and destination vertices,
        if we reverse the direction of all edges in the graph, the shortest path length should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Create a new graph with reversed edges
        reversed_graph = np.transpose(graph)

        # Get follow-up output
        follow_out = shortest_path(reversed_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()