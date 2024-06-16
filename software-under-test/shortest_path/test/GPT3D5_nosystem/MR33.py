import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test33(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 33: Given the same graph, the same source and destination vertices, if the graph contains negative weight cycles,
        the shortest path distances may not be well-defined and should return negative infinity."""
        # Get source output
        source_out = shortest_path(graph, method=method)

        graph_with_negative_cycle = graph.copy()
        graph_with_negative_cycle[0][0] = -1

        # Get follow-up output
        follow_out = shortest_path(graph_with_negative_cycle, method=method)

        # Verification
        self.assertTrue(np.array_equal(follow_out, np.full_like(source_out, -np.inf)))


if __name__ == "__main__":
    unittest.main()
