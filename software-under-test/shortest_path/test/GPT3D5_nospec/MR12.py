import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test12(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 12: Given the same graph, source, and destination vertices, 
        if the graph is transformed into its transpose, then the shortest path from source to destination in the original
        graph should be the same as the shortest path from destination to source in the transposed graph."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with transposed graph
        transposed_graph = list(map(list, zip(*graph)))

        # Get follow-up output
        follow_out = shortest_path(transposed_graph, method=method)[dst][src]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
