import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 9: Given the same graph, source and destination vertices, 
        if all edge weights are increased by a constant value, the shortest path should remain the same."""
        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Construct follow-up input with increased edge weights
        follow_graph = [[x + 5 for x in row] for row in graph]

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
