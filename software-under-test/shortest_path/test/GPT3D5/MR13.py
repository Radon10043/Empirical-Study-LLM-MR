import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test13(self, graph: list, src: int, dst: int, method: str): # Fixed
        """Metamorphic Relation 13: Given the same graph, the same source and destination vertices,
        but with the graph modified to have additional vertices and edges, the result should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Modify the graph to have additional vertices and edges
        follow_graph = graph.copy()
        for row in follow_graph:
            row.append(0)
        follow_graph.append([0] * (len(graph)+1))

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
