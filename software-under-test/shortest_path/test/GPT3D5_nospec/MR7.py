import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test7(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 7: Given the same graph, the same source and destination vertices,
        but with the weights incremented by a constant, the output should be incremented by the same constant."""
        constant = 10  # increment constant

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        follow_graph = [[x + constant for x in row] for row in graph]  # incrementing all weights by the constant

        # Get follow-up output
        follow_out = shortest_path(follow_graph, method)[src][dst]

        # Verification
        self.assertEqual(source_out + constant, follow_out)


if __name__ == "__main__":
    unittest.main()
