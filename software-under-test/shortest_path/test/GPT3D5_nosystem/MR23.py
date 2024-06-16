import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test23(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 23: Given the same graph, the same source and destination vertices,
        changing the order of the vertices indices should not change the shortest path length."""

        # Get source output
        source_out = shortest_path(graph, method=method)

        # Create a new graph with reordered vertices
        reordered_graph = graph.copy()
        np.random.shuffle(reordered_graph)

        # Get follow-up output
        follow_out = shortest_path(reordered_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
