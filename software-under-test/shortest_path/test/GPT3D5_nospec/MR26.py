import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test26(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 26: Given the same graph, the same source and destination vertices, 
        if an alternative path is added with a higher cost, the shortest path method should still produce the original shortest path."""
        modified_graph = [row[:] for row in graph]
        modified_graph[src][dst] = 100  # Adding an alternative path with a higher cost

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
