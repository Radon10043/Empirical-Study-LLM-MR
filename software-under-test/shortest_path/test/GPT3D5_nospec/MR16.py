import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test16(self, graph: list, src: int, dst: int, method: str):
        """"Metamorphic Relation: Given the same graph, source, and destination vertices,
        if the graph is modified by adding or removing redundant edges without changing the shortest path, 
        the shortest path should remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding or removing redundant edges
        follow_graph = modify_graph_redundant_edges(graph)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
