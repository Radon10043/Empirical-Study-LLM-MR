import os, sys

sys.path.append(os.path.dirname(os.path.dirname(__file__)))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(gen_tcs_randomly(1000))
    def test9(self, graph: list, src: int, dst: int, method: str):
        """Metamorphic Relation 9: Given the same graph, the same source and destination vertices,
        but with the graph's edges reversed, the output should be the same."""
        reversed_graph = [list(x) for x in zip(*graph)]  # reverse the edges of the graph

        # Get source output
        source_out = shortest_path(graph, method=method)[src][dst]

        # Get follow-up output
        follow_out = shortest_path(reversed_graph, method=method)[src][dst]

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
