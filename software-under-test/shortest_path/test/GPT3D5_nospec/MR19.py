import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test19(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 19: Given the graph and source and destination vertices, 
        if we add a new edge between any two vertices of the original graph,
        the shortest path in the new graph should be greater than or equal to the original shortest path."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input by adding a new edge between any two vertices of the original graph
        follow_graph = add_edge(graph)

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertGreaterEqual(follow_out, source_out)


if __name__ == "__main__":
    unittest.main()
