import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test24(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 24: Given the same graph, the same source and destination vertices, 
        but with additional weights assigned to certain edges, the shortest path satisfies the updated weights."""
        modified_graph = [row[:] for row in graph]
        modified_graph[0][1] = 10  # Assigning additional weight to an edge

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(modified_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
