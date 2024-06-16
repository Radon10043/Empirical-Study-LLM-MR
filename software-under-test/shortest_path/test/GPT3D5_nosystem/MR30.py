import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test30(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 30: Given the same graph and the same source and destination vertices, if the graph is converted into an unweighted graph (by setting all non-zero weights to 1), the shortest path should remain unchanged."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        # Convert the graph to an unweighted graph
        unweighted_graph = [[1 for x in row] for row in graph]

        # Get follow-up output for the unweighted graph
        follow_out = shortest_path(unweighted_graph, method=method)

        # Verification
        self.assertTrue(np.array_equal(source_out, follow_out))


if __name__ == "__main__":
    unittest.main()
