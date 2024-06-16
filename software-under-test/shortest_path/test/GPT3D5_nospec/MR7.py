import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: Given the same graph, but with an additional vertex added to the graph,
        the shortest path from source to destination should not be longer than the original shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with an additional vertex
        follow_graph = [row + [float('inf')] for row in graph] + [[float('inf')] * (len(graph[0]) + 1)]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertLessEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
